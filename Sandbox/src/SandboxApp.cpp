#include <Luci.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f, true) {
		m_VertexArray.reset(Luci::VertexArray::Create());

		float vertices[4 * (3 + 2)] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Luci::Ref<Luci::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Luci::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float)));
		vertexBuffer->SetLayout({
			{ Luci::ShaderDataType::Float3, "a_Position" },
			{ Luci::ShaderDataType::Float2, "a_TexCoord" },
		});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[2 * 3] = {
			0, 1, 2,
			0, 2, 3,
		};

		Luci::Ref<Luci::IndexBuffer> indexBuffer;
		indexBuffer.reset(Luci::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Luci::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureIcon = Luci::Texture2D::Create("assets/textures/Icon.png");

		std::dynamic_pointer_cast<Luci::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Luci::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Luci::Timestep timestep) override {
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

	void OnEvent(Luci::Event& event) override {
		m_CameraController.OnEvent(event);
	}

private:
	Luci::ShaderLibrary m_ShaderLibrary;

	Luci::Ref<Luci::VertexArray> m_VertexArray;
	Luci::Ref<Luci::Texture> m_Texture, m_TextureIcon;

	Luci::OrthographicCameraController m_CameraController;
};

class Sandbox : public Luci::Application {
public:
	Sandbox() { PushLayer(new ExampleLayer()); }
	~Sandbox() = default;
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
