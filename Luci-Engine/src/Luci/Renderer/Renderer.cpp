#include "lucipch.h"

#include "Luci/Renderer/Renderer.h"
#include "Luci/Renderer/Renderer2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Luci {

	Scope <Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

	void Renderer::Initialize() {
		LUCI_PROFILE_FUNCTION();
		RenderCommand::Initialize();
		Renderer2D::Initialize();
	}

	void Renderer::Shutdown() {
		LUCI_PROFILE_FUNCTION();
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene() {
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
