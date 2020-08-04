#pragma once

#include "Camera/OrthographicCamera.h"
#include "Texture.h"

namespace Luci {

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& scale, const Ref<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& scale, const Ref<Texture2D> texture, const glm::vec4& color = glm::vec4(1.0f));
	};

}
