#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	m_Texture = Luci::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureIcon = Luci::Texture2D::Create("assets/textures/Icon.png");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Luci::Timestep timestep) {
	m_CameraController.OnUpdate(timestep);

	Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Luci::RenderCommand::Clear();

	Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Luci::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.6f, 0.7f }, m_SquareColor);
	Luci::Renderer2D::DrawQuad({ 0.6f, -0.5f }, { 1.0f, 0.8f }, { 0.3f, 0.2f, 0.8f, 1.0f });
	Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f }, { 0.5f, 0.5f }, m_Texture, { 1.0f, 0.7f, 0.8f, 0.9f });
	Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f, 0.1f }, { 0.6f, 0.6f }, m_TextureIcon, glm::vec4(1.0f));

	Luci::Renderer2D::EndScene();
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
