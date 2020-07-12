#pragma once

#include "Core.h"
#include "Window.h"
#include "Luci/LayerStack.h"
#include "Luci/Events/Event.h"
#include "Luci/Events/ApplicationEvent.h"

namespace Luci {

	class LUCI_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		static Application* s_Instance;

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& event);
	};

	// to be defined in client
	Application* CreateApplication();

}
