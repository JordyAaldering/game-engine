#include "ExampleLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("Example"), m_CameraController(1280.0f / 720.0f, true) {
	m_VertexArray = Luci::VertexArray::Create();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};

	Luci::Ref<Luci::VertexBuffer> vertexBuffer;
	vertexBuffer = Luci::VertexBuffer::Create(vertices, sizeof(vertices));
	vertexBuffer->SetLayout({
		{ Luci::ShaderDataType::Float3, "a_Position" },
		{ Luci::ShaderDataType::Float2, "a_TexCoord" },
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
	Luci::Ref<Luci::IndexBuffer> indexBuffer;
	indexBuffer = Luci::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
	m_Texture = Luci::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TextureIcon = Luci::Texture2D::Create("assets/textures/Icon.png");

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach() {}

void ExampleLayer::OnDetach() {}

void ExampleLayer::OnUpdate(Luci::Timestep timestep) {
	m_CameraController.OnUpdate(timestep);

	Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Luci::RenderCommand::Clear();

	Luci::Renderer::BeginScene(m_CameraController.GetCamera());

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Luci::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));
	m_TextureIcon->Bind();
	Luci::Renderer::Submit(textureShader, m_VertexArray, glm::mat4(1.0f));

	Luci::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
