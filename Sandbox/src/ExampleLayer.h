#pragma once

#include "Luci.h"

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer();
	~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Luci::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Luci::Event& event) override;

private:
	Luci::OrthographicCameraController m_CameraController;

	Luci::ShaderLibrary m_ShaderLibrary;
	Luci::Ref<Luci::VertexArray> m_VertexArray;
	Luci::Ref<Luci::Texture> m_Texture, m_TextureIcon;

	glm::vec4 m_QuadColor = glm::vec4(1.0f);
};
