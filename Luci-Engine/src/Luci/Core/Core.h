#pragma once

#include <memory>

// Platform detection
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
#endif // End of platform detection

// DLL support
#ifdef LUCI_PLATFORM_WINDOWS
	#if LUCI_DYNAMIC_LINK
		#ifdef LUCI_BUILD_DLL
			#define HAZEL_API __declspec(dllexport)
		#else
			#define HAZEL_API __declspec(dllimport)
		#endif
	#else
		#define LUCI_API
	#endif
#else
	#error Luci only supports Windows!
#endif // End of DLL support

#ifdef LUCI_DEBUG
	#define LUCI_ENABLE_ASSERTS
#endif

#ifdef LUCI_ENABLE_ASSERTS
	#define LUCI_ASSERT(x, ...)      { if(!(x)) { LUCI_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LUCI_CORE_ASSERT(x, ...) { if(!(x)) { LUCI_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LUCI_ASSERT(x, ...)
	#define LUCI_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LUCI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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
