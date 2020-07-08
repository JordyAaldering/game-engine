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
