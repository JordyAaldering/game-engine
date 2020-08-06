#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWDDDDDDWWWWWWWWWWWW"
"WWWWWDDDDDDDDDDWWWWWWWWW"
"WWWWDDDDDDDDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDDWWWWW"
"WWWDDDDDDDDWWWDDDDDDWWWW"
"WWWDDDDDDDDWWWDDDDDDWWWW"
"WWWWDDDDDDDDWWDDDDDDWWWW"
"WWWWWDDDDDDDDDDDDDDDDWWW"
"WWWWWWDDDDDDDDDDDDDDDWWW"
"WWWWWWDDDDDDDDDDDDDDDWWW"
"WWWWWWWDDWWWWDDDDDDDWWWW"
"WWWWWWWWWWWWWWWWDDDWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";
static const uint32_t s_MapWidth = 24;
static const uint32_t s_MapHeight = strlen(s_MapTiles) / s_MapWidth;

Sandbox2D::Sandbox2D() : Layer("GameLayer"), m_CameraController(1280.0f / 720.0f) {}

void Sandbox2D::OnAttach() {
	LUCI_PROFILE_FUNCTION();

	m_SpriteSheet = Luci::Texture2D::Create("assets/textures/RPGPack.png");
	m_ErrorTexture = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 3, 3 }, { 128, 128 });
	m_TextureMap['W'] = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });
	m_TextureMap['D'] = Luci::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });

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
	for (uint32_t y = 0; y < s_MapHeight; y++) {
		for (uint32_t x = 0; x < s_MapWidth; x++) {
			char tileType = s_MapTiles[x + y * s_MapWidth];

			Luci::Ref<Luci::SubTexture2D> texture;
			if (m_TextureMap.find(tileType) != m_TextureMap.end()) {
				texture = m_TextureMap[tileType];
			}
			else {
				texture = m_ErrorTexture;
			}

			Luci::Renderer2D::DrawQuad({ x - s_MapWidth * 0.5f, y - s_MapHeight * 0.5f }, 0, { 1.0f, 1.0f }, texture);
		}
	}
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
