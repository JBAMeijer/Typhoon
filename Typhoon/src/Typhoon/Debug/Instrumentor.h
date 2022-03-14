//
// Basic instrumentation profiler by Cherno

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session 
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__ for the profile name.
//
#pragma once
#include "Typhoon/Core/Base.h"

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <thread>

namespace Typhoon {

    using FPMicroSeconds = std::chrono::duration<double, std::micro>;

    struct ProfileResult
    {
        std::string Name;
        FPMicroSeconds Start;
        std::chrono::microseconds ElapsedTime;
        std::thread::id ThreadID;
    };

    class Instrumentor
    {
    public:
        Instrumentor()
            : m_CurrentSession(""), m_ActiveSession(false)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(m_Mutex);
            if (m_ActiveSession)
            {
                // If there is already a current session, then close it before beginning new one.
                // Subsequent profiling output meant for the original session will end up in the
                // newly opened session instead.  That's better than having badly formatted
                // profiling output.
                if (Log::GetCoreLogger()) // Edge case: BeginSession() might be before Log::Init()
                    TYPH_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession);

                InternalEndSession();
            }
            m_OutputStream.open(filepath);

            if (m_OutputStream.is_open()) 
            {
                m_CurrentSession = name;
                WriteHeader();
            }
            else 
            {
                if (Log::GetCoreLogger())  // Edge case: BeginSession() might be before Log::Init()
                    TYPH_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
            }
            
            m_ActiveSession = true;
        }

        void EndSession()
        {   
            std::lock_guard lock(m_Mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;

            json << std::setprecision(3) << std::fixed;
            json << ",{";
            json << "\"cat\":\"function\",";
            json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
            json << "\"name\":\"" << result.Name << "\",";
            json << "\"ph\":\"X\",";
            json << "\"pid\":0,";
            json << "\"tid\":" << result.ThreadID << ",";
            json << "\"ts\":" << result.Start.count();
            json << "}";


            std::lock_guard lock(m_Mutex);
            if (m_ActiveSession)
            {
                m_OutputStream << json.str();
                m_OutputStream.flush();
            }
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }


        // Note: you must already own lock on m_Mutex before
        // calling InternalEndSession()
        void InternalEndSession() 
        {
            if (m_ActiveSession) 
            {
                WriteFooter();
                m_OutputStream.close();
                m_ActiveSession = false;
                m_CurrentSession.clear();
            }
        }

    private:
        std::mutex m_Mutex;
        std::ofstream m_OutputStream;
        std::string m_CurrentSession;
        bool m_ActiveSession;
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimePoint = std::chrono::steady_clock::now();
            auto highResStart = FPMicroSeconds{ m_StartTimepoint.time_since_epoch() };
            auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

            Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id()});

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
        bool m_Stopped;
    };

    namespace InstrumentorUtils
    {
        template <size_t N>
        struct ChangeResult
        {
            char Data[N];
        };

        template <size_t N, size_t K>
        constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
        {
            ChangeResult<N> result = {};

            size_t srcIndex = 0;
            size_t dstIndex = 0;
            while (srcIndex < N)
            {
                size_t matchIndex = 0;
                while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
                    matchIndex++;
                if (matchIndex == K - 1)
                    srcIndex += matchIndex;
                result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
                srcIndex++;
            }
            return result;
        }
    }

}

#if defined(TYPH_ENABLE_PROFILE)
    #if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
        #define TYPH_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(__DMC__) && (__DMC__ >= 0x810)
        #define TYPH_FUNC_SIG __PRETTY_FUNCTION__
    #elif (defined(__FUNCSIG__) || (_MSC_VER))
        #define TYPH_FUNC_SIG __FUNCSIG__
    #elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
        #define TYPH_FUNC_SIG __FUNCTION__
    #elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
        #define TYPH_FUNC_SIG __FUNC__
    #elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
        #define TYPH_FUNC_SIG __func__
    #elif defined(__cplusplus) && (__cplusplus >= 201103)
        #define TYPH_FUNC_SIG __func__
    #else
        #define TYPH_FUNC_SIG "HZ_FUNC_SIG unknown!"
    #endif

    #define TYPH_PROFILE_BEGIN_SESSION(name, filepath) ::Typhoon::Instrumentor::Get().BeginSession(name, filepath)
    #define TYPH_PROFILE_END_SESSION() ::Typhoon::Instrumentor::Get().EndSession()
    #define TYPH_PROFILE_SCOPE(name) constexpr auto fixedName = ::Typhoon::InstrumentorUtils::CleanupOutputString(name, "__cdecl "); \
                                           ::Typhoon::InstrumentationTimer TOKENPASTE2(timer, __LINE__)(fixedName.Data)
    #define TYPH_PROFILE_FUNCTION() TYPH_PROFILE_SCOPE(TYPH_FUNC_SIG)
#else
    #define TYPH_PROFILE_BEGIN_SESSION(name, filepath)
    #define TYPH_PROFILE_END_SESSION()
    #define TYPH_PROFILE_SCOPE(name)
    #define TYPH_PROFILE_FUNCTION()
#endif