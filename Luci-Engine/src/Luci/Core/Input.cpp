#include "lucipch.h"
#include "Input.h"

#ifdef LUCI_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Luci {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create() {
		#ifdef LUCI_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			LUCI_CORE_ASSERT(false, "Unknown platform.");
			return nullptr;
		#endif
	}

}
