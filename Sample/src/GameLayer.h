#pragma once

#include "Luci.h"

class GameLayer : public Luci::Layer {
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Luci::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Luci::Event& event) override;

private:
	Luci::OrthographicCameraController m_CameraController;

	Luci::Ref<Luci::VertexArray> m_VertexArray;
	Luci::Ref<Luci::Shader> m_Shader;

	Luci::Ref<Luci::Texture2D> m_SpriteSheet;
	Luci::Ref<Luci::SubTexture2D> m_ErrorTexture;
	std::unordered_map<char, Luci::Ref<Luci::SubTexture2D>> m_TextureMap;

};
