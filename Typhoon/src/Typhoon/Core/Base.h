#pragma once

#include <memory>

// Platform detection
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define TYPH_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "32-bit builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MAC__)
	#include <TargetConditionals>
	/* The TARGET_OS_MAC macro exists on all apple related platforms.
	 * We must first check the platform specific ones before checking this one
	 * to ensure that we're running on a MAC and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define TYPH_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define TYPH_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check the __ANDROID__ macro before __linux__ 
   Since android is based on the Linux kernel it also has the
   __linux__ macro defined */
#elif defined(__ANDROID__)
	#define TYPH_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define TYPH_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown platform */
	#error "Unknown platform!"
#endif 
// End of platform detection

#if defined(TYPH_DEBUG)
	#if defined(TYPH_PLATFORM_WINDOWS)
		#define TYPH_DEBUGBREAK() __debugbreak()
	#elif
		#include <signal.h>
		#define TYPH_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	
	//#define TYPH_ENABLE_PROFILE
	#define TYPH_ENABLE_ASSERTS

#else
	#define TYPH_DEBUGBREAK()
#endif

#ifdef TYPH_ENABLE_ASSERTS
	#define TYPH_CLIENT_ASSERT(x, ...) { if(!(x)) { TYPH_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); TYPH_DEBUGBREAK(); } }
	#define TYPH_CORE_ASSERT(x, ...) { if(!(x)) { TYPH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); TYPH_DEBUGBREAK(); } }
#else
	#define TYPH_CLIENT_ASSERT(x, ...)
	#define TYPH_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TYPH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

namespace Typhoon
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}