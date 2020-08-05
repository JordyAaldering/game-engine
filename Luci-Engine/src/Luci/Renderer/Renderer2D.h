#pragma once

#include "Camera/OrthographicCamera.h"
#include "Luci/Renderer/Texture.h"
#include "Luci/Renderer/SubTexture2D.h"

namespace Luci {

	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const glm::vec4& color = glm::vec4(1.0f));
	
		// Statistics
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetVertexCount() { return QuadCount * 4; }
			uint32_t GetIndexCount() { return QuadCount * 6; }
		};

		static void ResetStatistics();
		static Statistics GetStatistics();

	private:
		static void FlushAndReset();

		// Primitives
		static void DrawQuadFromTexIndex(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color, float texIndex, const glm::vec2* texCoords);
	};

}
