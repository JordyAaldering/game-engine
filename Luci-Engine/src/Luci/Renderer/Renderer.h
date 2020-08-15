#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Renderer/Shader.h"
#include "Luci/Renderer/RenderCommand.h"
#include "Luci/Renderer/Camera/OrthographicCamera.h"

namespace Luci {
	
	class Renderer {
	public:
		static void Initialize();
		static void Shutdown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};

}
