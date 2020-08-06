#include "lucipch.h"
#include "Window.h"

#ifdef LUCI_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Luci {

	Scope<Window> Window::Create(const WindowProps& props) {
		#ifdef LUCI_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			LUCI_CORE_ASSERT(false, "Unknown platform.");
			return nullptr;
		#endif
	}

}
