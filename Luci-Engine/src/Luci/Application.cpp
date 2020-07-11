#include "lucipch.h"
#include "Application.h"

#include "Luci/Events/ApplicationEvent.h"
#include "Luci/Log.h"

namespace Luci {

	Application::Application() {}
	Application::~Application() {}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		LUCI_TRACE(e);
	}

}
