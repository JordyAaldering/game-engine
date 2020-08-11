#pragma once

#include <memory>

/*
 * Platform detection
 */

#ifdef _WIN32
	#ifdef _WIN64
		#define LUCI_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define LUCI_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define LUCI_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define LUCI_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define LUCI_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

/*
 * Debugging
 */

#ifdef LUCI_DEBUG
	#define LUCI_ENABLE_ASSERTS
	#if defined(LUCI_PLATFORM_WINDOWS)
		#define LUCI_DEBUG_BREAK() __debugbreak()
	#elif defined(LUCI_PLATFORM_LINUX)
		#include <signal.h>
		#define LUCI_DEBUG_BREAK() raise(SIGTRAP)
	#else
		#error "Platform does not support debugbreak!"
	#endif
#else
	#define LUCI_DEBUG_BREAK()
#endif

#ifdef LUCI_ENABLE_ASSERTS
	#define LUCI_ASSERT(x, ...)      { if(!(x)) { LUCI_ERROR("Assertion failed: {0}", __VA_ARGS__); LUCI_DEBUG_BREAK(); } }
	#define LUCI_CORE_ASSERT(x, ...) { if(!(x)) { LUCI_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); LUCI_DEBUG_BREAK(); } }
#else
	#define LUCI_ASSERT(x, ...)
	#define LUCI_CORE_ASSERT(x, ...)
#endif

/*
 * Utilities 
 */

#define LUCI_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Luci {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
