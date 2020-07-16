#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Window.h"
#include "LayerStack.h"

#include "Luci/Events/Event.h"
#include "Luci/Events/ApplicationEvent.h"
#include "Luci/ImGui/ImGuiLayer.h"

#include "Luci/Renderer/Shader.h"
#include "Luci/Renderer/VertexArray.h"
#include "Luci/Renderer/Buffer.h"
#include "Luci/Renderer/OrthographicCamera.h"

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
		float m_LastFrameTime = 0.0f;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent& event);
	};

	/// <summary>
	/// Creates a new application as defined by the client.
	/// </summary>
	Application* CreateApplication();

}
