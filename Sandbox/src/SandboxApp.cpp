#include <Luci.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
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

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main() {
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main() {
				o_Color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader.reset(Luci::Shader::Create(vertexSrc, fragmentSrc));
		m_Texture = Luci::Texture2D::Create("assets/textures/Icon.png");

		std::dynamic_pointer_cast<Luci::OpenGLShader>(m_Texture)->Bind();
		std::dynamic_pointer_cast<Luci::OpenGLShader>(m_Texture)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Luci::Timestep timestep) override {
		if (Luci::Input::IsKeyPressed(LUCI_KEY_A)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_D)) {
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}
		if (Luci::Input::IsKeyPressed(LUCI_KEY_W)) {
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_S)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}
		if (Luci::Input::IsKeyPressed(LUCI_KEY_Q)) {
			m_CameraRotation += m_CameraRotateSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_E)) {
			m_CameraRotation -= m_CameraRotateSpeed * timestep;
		}

		Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Luci::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Luci::Renderer::BeginScene(m_Camera);
		m_Texture->Bind();
		Luci::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
		Luci::Renderer::EndScene();
	}

private:
	Luci::Ref<Luci::Shader> m_Shader;
	Luci::Ref<Luci::VertexArray> m_VertexArray;
	Luci::Ref<Luci::Texture> m_Texture;

	Luci::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotateSpeed = 90.0f;
};

class Sandbox : public Luci::Application {
public:
	Sandbox() { PushLayer(new ExampleLayer()); }
	~Sandbox() = default;
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
