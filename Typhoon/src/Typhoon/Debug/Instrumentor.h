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

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

#include "Typhoon/Core/Base.h"

namespace Typhoon {

    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    class Instrumentor
    {
    public:
        Instrumentor()
            : m_CurrentSession("Undefined"), m_ProfileCount(0), m_ActiveSession(false)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            if (m_ActiveSession) EndSession();
            m_ActiveSession = true;
            m_OutputStream.open(filepath);
            WriteHeader();
            m_CurrentSession = name;
        }

        void EndSession()
        {
            if (!m_ActiveSession) return;
            m_ActiveSession = false;
            WriteFooter();
            m_OutputStream.close();
            m_CurrentSession = "Undefined";
            m_ProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";

            m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        std::ofstream m_OutputStream;
        int m_ProfileCount;
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
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

            m_Stopped = true;
        }
    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };

}

#if defined(TYPH_ENABLE_PROFILE)
    #define TYPH_PROFILE_BEGIN_SESSION(name, filepath) ::Typhoon::Instrumentor::Get().BeginSession(name, filepath)
    #define TYPH_PROFILE_END_SESSION() ::Typhoon::Instrumentor::Get().EndSession()
    #define TYPH_PROFILE_SCOPE(name) ::Typhoon::InstrumentationTimer timer##__LINE__(name)
    #define TYPH_PROFILE_FUNCTION() TYPH_PROFILE_SCOPE(__FUNCSIG__)
#else
    #define TYPH_PROFILE_BEGIN_SESSION(name, filepath)
    #define TYPH_PROFILE_END_SESSION()
    #define TYPH_PROFILE_SCOPE(name)
    #define TYPH_PROFILE_FUNCTION()
#endif