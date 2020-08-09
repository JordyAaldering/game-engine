#include "lucipch.h"
#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Luci {

    EditorLayer::EditorLayer()
        : Layer("GameLayer"), m_CameraController(1280.0f / 720.0f) {
    }

    void EditorLayer::OnAttach() {
        LUCI_PROFILE_FUNCTION();

        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbSpec);

        m_SpriteSheet = Texture2D::Create("assets/textures/RPGPack.png");
        m_WaterTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });
        m_DirtTexture = SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });

        m_CameraController.SetZoomLevel(5.0f);
    }

    void EditorLayer::OnDetach() {
        LUCI_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Timestep timestep) {
        LUCI_PROFILE_FUNCTION();

        if (m_ViewportFocused) {
            m_CameraController.OnUpdate(timestep);
        }

        Renderer2D::ResetStatistics();
        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (int y = -5; y <= 5; y++) {
            for (int x = -5; x <= 5; x++) {
                Ref<SubTexture2D> texture = (x + y) % 2 == 0 ? m_WaterTexture : m_DirtTexture;
                Renderer2D::DrawQuad({ x, y }, 0, { 0.9f, 0.9f }, texture);
            }
        }
        Renderer2D::EndScene();

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender() {
        LUCI_PROFILE_FUNCTION();

        static bool dockspaceOpen = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen) {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen) {
            ImGui::PopStyleVar(2);
        }

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Exit")) {
                    Application::Get().Close();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        auto stats = Renderer2D::GetStatistics();
        ImGui::Begin("Statistics");
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetVertexCount());
        ImGui::Text("Indices: %d", stats.GetIndexCount());
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if ((viewportPanelSize.x != m_ViewportSize.x || viewportPanelSize.y != m_ViewportSize.y)
            && viewportPanelSize.x > 0 && viewportPanelSize.y > 0) {
            m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.Resize(m_ViewportSize.x, m_ViewportSize.y);
        }

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();

        ImGui::End();
    }

    void EditorLayer::OnEvent(Event& event) {
        m_CameraController.OnEvent(event);
    }

}
