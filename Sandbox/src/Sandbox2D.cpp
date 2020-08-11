#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("GameLayer"), m_CameraController(1280.0f / 720.0f) {
}

void Sandbox2D::OnAttach() {
	LUCI_PROFILE_FUNCTION();

	m_SpriteSheet = Luci::Texture2D::Create("assets/textures/RPGPack.png");
	m_Texture = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 3 }, { 128, 128 });
	m_CameraController.SetZoomLevel(5.0f);
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

	Luci::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Luci::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	LUCI_PROFILE_FUNCTION();

    auto stats = Luci::Renderer2D::GetStatistics();
    ImGui::Begin("Statistics");
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::Text("Vertices: %d", stats.GetVertexCount());
    ImGui::Text("Indices: %d", stats.GetIndexCount());
    ImGui::End();
}

void Sandbox2D::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
