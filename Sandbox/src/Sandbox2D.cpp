#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

template<typename Fn>
class Timer {
public:
	Timer(const char* name, Fn&& function)
		: m_Name(name), m_Function(function), m_Stopped(false) {
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer() {
		if (!m_Stopped) {
			Stop();
		}
	}

	void Stop() {
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;
		float duration = (end - start) * 0.001f;
		m_Function({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn m_Function;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	m_Texture = Luci::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureIcon = Luci::Texture2D::Create("assets/textures/Icon.png");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Luci::Timestep timestep) {
	PROFILE_SCOPE("Sandbox2D::OnUpdate");

	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(timestep);
	}

	{
		PROFILE_SCOPE("Renderer Preparation");
		Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Luci::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Renderer Draw");
		Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());

		Luci::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.6f, 0.7f }, m_SquareColor);
		Luci::Renderer2D::DrawQuad({ 0.6f, -0.5f }, { 1.0f, 0.8f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f }, { 0.5f, 0.5f }, m_Texture, { 1.0f, 0.7f, 0.8f, 0.9f });
		Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f, 0.1f }, { 0.6f, 0.6f }, m_TextureIcon, glm::vec4(1.0f));

		Luci::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

	for (auto& result : m_ProfileResults) {
		char label[50];
		strcpy_s(label, "%.3fms  ");
		strcat_s(label, result.Name);
		ImGui::Text(label, result.Time);
	}

	m_ProfileResults.clear();
	ImGui::End();
}

void Sandbox2D::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
