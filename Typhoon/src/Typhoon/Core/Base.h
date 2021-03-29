#pragma once

#include <memory>

#ifdef TYPH_PLATFORM_WINDOWS
#if TYPH_DYNAMIC_LINK
	#ifdef TYPH_BUILD_DLL
		#define TYPHOON_API __declspec(dllexport)
	#else 
		#define TYPHOON_API __declspec(dllimport)
	#endif
#else
	#define TYPHOON_API
#endif
#else
#error Typhoon only supports windows!
#endif

#ifdef TYPH_DEBUG
	#define TYPH_ENABLE_ASSERTS
#endif

#ifdef TYPH_ENABLE_ASSERTS
	#define TYPH_CLIENT_ASSERT(x, ...) { if(!(x)) { TYPH_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TYPH_CORE_ASSERT(x, ...) { if(!(x)) { TYPH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TYPH_CLIENT_ASSERT(x, ...)
	#define TYPH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TYPH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Typhoon
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}