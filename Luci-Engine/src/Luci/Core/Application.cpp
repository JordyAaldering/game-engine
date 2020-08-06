#include "lucipch.h"
#include "Application.h"

#include "Luci/Core/Input.h"
#include "Luci/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Luci {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		LUCI_PROFILE_FUNCTION();

		LUCI_CORE_ASSERT(!s_Instance, "Application already exists.");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(LUCI_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {
		LUCI_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void Application::Run() {
		LUCI_PROFILE_FUNCTION();

		while (m_Running) {
			LUCI_PROFILE_SCOPE("Application::Run Loop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				LUCI_PROFILE_SCOPE("Application::Run LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			{
				LUCI_PROFILE_SCOPE("Application::Run LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::Close() {

	}

	void Application::OnEvent(Event& event) {
		LUCI_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(LUCI_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LUCI_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(event);
			if (event.Handled) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer) {
		LUCI_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		LUCI_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		LUCI_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}

}
