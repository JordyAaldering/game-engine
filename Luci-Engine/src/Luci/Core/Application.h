#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Luci/Events/Event.h"
#include "Luci/Events/ApplicationEvent.h"
#include "Luci/ImGui/ImGuiLayer.h"

#include "Luci/Renderer/Shader.h"

namespace Luci {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

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
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		bool OnWindowClose(WindowCloseEvent& event);
	};

	// to be defined in client
	Application* CreateApplication();

}
