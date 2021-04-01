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

// DLL support
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
// End of DLL support

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