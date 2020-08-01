#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {
	
}

void Sandbox2D::OnAttach() {
	m_VertexArray = Luci::VertexArray::Create();

	float vertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f,
	};

	Luci::Ref<Luci::VertexBuffer> vertexBuffer = Luci::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));
	vertexBuffer->SetLayout({
		{ Luci::ShaderDataType::Float3, "a_Position" },
	});
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[2 * 3] = {
		0, 1, 2,
		0, 2, 3,
	};

	Luci::Ref<Luci::IndexBuffer> indexBuffer = Luci::IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = Luci::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach() {

}

void Sandbox2D::OnUpdate(Luci::Timestep timestep) {
	m_CameraController.OnUpdate(timestep);

	Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Luci::RenderCommand::Clear();

	Luci::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Luci::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Luci::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Luci::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Luci::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Luci::Event& event) {
	m_CameraController.OnEvent(event);
}
