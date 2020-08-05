#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
	LUCI_PROFILE_FUNCTION();
	m_Texture = Luci::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureIcon = Luci::Texture2D::Create("assets/textures/Icon.png");
}

void Sandbox2D::OnDetach() {
	LUCI_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Luci::Timestep timestep) {
	LUCI_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(timestep);

	Luci::Renderer2D::ResetStatistics();
	Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Luci::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += timestep * 20;

	Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Luci::Renderer2D::DrawQuad({ -1.0f, -0.2f }, 0.0f, { 0.6f, 0.7f }, m_SquareColor);
	Luci::Renderer2D::DrawQuad({ 0.6f, -0.5f }, 0.0f, { 1.0f, 0.8f }, { 0.2f, 0.8f, 0.3f, 1.0f });
	Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f }, glm::radians(rotation), { 0.5f, 0.5f }, m_Texture, { 1.0f, 0.7f, 0.8f, 0.9f });
	Luci::Renderer2D::DrawQuad({ -0.3f, 0.2f, 0.1f }, 0.0f, { 0.6f, 0.6f }, m_TextureIcon, glm::vec4(1.0f));
	Luci::Renderer2D::EndScene();

	Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5.1f; y += 0.5f) {
		for (float x = -5.0f; x < 5.1f; x += 0.5f) {
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.3f, (y + 5.0f) / 10.0f, 1.0f };
			Luci::Renderer2D::DrawQuad({ x, y }, 0.0f, { 0.45f, 0.45f }, color);
		}
	}
	Luci::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	LUCI_PROFILE_FUNCTION();

	auto stats = Luci::Renderer2D::GetStatistics();
	ImGui::Begin("ImGui");
	ImGui::Text("SETTINGS:");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::NewLine();

	ImGui::Text("STATISTICS:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetVertexCount());
	ImGui::Text("Indices: %d", stats.GetIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
