#pragma once

#include "Typhoon/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Typhoon {

	class TYPHOON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define TYPH_CORE_CRITICAL(...)	::Typhoon::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define TYPH_CORE_ERROR(...)		::Typhoon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TYPH_CORE_WARN(...)		::Typhoon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TYPH_CORE_INFO(...)		::Typhoon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TYPH_CORE_TRACE(...)	    ::Typhoon::Log::GetCoreLogger()->trace(__VA_ARGS__)

// Client log macros
#define TYPH_CLIENT_CRITICAL(...) ::Typhoon::Log::GetClientLogger()->critical(__VA_ARGS__)
#define TYPH_CLIENT_ERROR(...)	::Typhoon::Log::GetClientLogger()->error(__VA_ARGS__)
#define TYPH_CLIENT_WARN(...)		::Typhoon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TYPH_CLIENT_INFO(...)		::Typhoon::Log::GetClientLogger()->info(__VA_ARGS__)
#define TYPH_CLIENT_TRACE(...)	::Typhoon::Log::GetClientLogger()->trace(__VA_ARGS__)