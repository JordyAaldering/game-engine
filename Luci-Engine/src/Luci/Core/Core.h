#pragma once

#ifdef LUCI_DEBUG
	#define LUCI_ENABLE_ASSERTS
#endif // LUCI_DEBUG

#ifdef LUCI_ENABLE_ASSERTS
	#define LUCI_ASSERT(x, ...)      { if(!(x)) { LUCI_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define LUCI_CORE_ASSERT(x, ...) { if(!(x)) { LUCI_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LUCI_ASSERT(x, ...)
	#define LUCI_CORE_ASSERT(x, ...)
#endif // LUCI_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define LUCI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
