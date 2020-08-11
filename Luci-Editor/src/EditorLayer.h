#pragma once

#include <Luci.h>

namespace Luci {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep timestep) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& event) override;

	private:
		OrthographicCameraController m_CameraController;

		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;

		Ref<Scene> m_ActiveScene;
		Entity m_CameraEntity;
		Entity m_QuadEntity;
		glm::vec4 m_QuadColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Texture2D> m_SpriteSheet;
		Ref<SubTexture2D> m_WaterTexture, m_DirtTexture;

	};

}
