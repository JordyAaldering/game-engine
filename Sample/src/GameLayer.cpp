#include "GameLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

GameLayer::GameLayer() : Layer("GameLayer"), m_CameraController(1280.0f / 720.0f) {}

void GameLayer::OnAttach() {
	LUCI_PROFILE_FUNCTION();

	m_SpriteSheet = Luci::Texture2D::Create("assets/textures/RPGPack.png");
	m_TextureBush = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 3 }, { 128, 128 });
	m_TextureBarrel = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 2 }, { 128, 128 });
	m_TextureTree = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
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
	Luci::Renderer2D::DrawQuad({ -1.0f, 0.0f }, glm::radians(30.0f), { 1.0f, 1.0f }, m_TextureBush);
	Luci::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f }, m_TextureBarrel);
	Luci::Renderer2D::DrawQuad({ 1.0f, 0.0f }, 0.0f, { 1.0f, 2.0f }, m_TextureTree);
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
