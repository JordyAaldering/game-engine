#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Luci/Events/ApplicationEvent.h"
#include "Window.h"

namespace Luci {

	class LUCI_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

		bool OnWindowClose(WindowCloseEvent& e);
	};

	// to be defined in client
	Application* CreateApplication();

}
