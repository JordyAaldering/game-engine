#pragma once

#ifdef LUCI_PLATFORM_WINDOWS
	#ifdef LUCI_BUILD_DLL
		#define LUCI_API __declspec(dllexport)
	#else
		#define LUCI_API __declspec(dllimport)
	#endif // LUCI_BUILD_DLL
#else
	#error Luci only supports Windows.
#endif // LUCI_PLATFORM_WINDOWS

#ifdef LUCI_ENABLE_ASSERTS
	#define LUCI_ASSERT(x, ...)      { if(!(x)) { LUCI_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LUCI_CORE_ASSERT(x, ...) { if(!(x)) { LUCI_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LUCI_ASSERT(x, ...)
	#define LUCI_CORE_ASSERT(x, ...)
#endif // LUCI_ENABLE_ASSERTS

#define BIT(x) (1 << x)
