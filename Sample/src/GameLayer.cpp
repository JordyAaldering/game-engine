#include "GameLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer() : Layer("GameLayer"), m_CameraController(1280.0f / 720.0f) {}

void GameLayer::OnAttach() {
	LUCI_PROFILE_FUNCTION();
	m_SpriteSheet = Luci::Texture2D::Create("assets/textures/RPGPack.png");
}

void GameLayer::OnDetach() {
	LUCI_PROFILE_FUNCTION();
}

void GameLayer::OnUpdate(Luci::Timestep timestep) {
	LUCI_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(timestep);

	Luci::Renderer2D::ResetStatistics();
	Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Luci::RenderCommand::Clear();

	Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Luci::Renderer2D::DrawQuad(glm::vec2(0.0f), 0.0f, glm::vec2(10.0f), m_SpriteSheet);
	Luci::Renderer2D::EndScene();
}

void GameLayer::OnImGuiRender() {
	LUCI_PROFILE_FUNCTION();

	auto stats = Luci::Renderer2D::GetStatistics();
	ImGui::Begin("Statistics");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetVertexCount());
	ImGui::Text("Indices: %d", stats.GetIndexCount());
	ImGui::End();
}

void GameLayer::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
