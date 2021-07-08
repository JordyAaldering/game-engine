#pragma once

#include "Luci/Core/Core.h"

#include "Luci/Renderer/Texture.h"
#include "Luci/Renderer/SubTexture2D.h"
#include "Luci/Renderer/Camera/Camera.h"
#include "Luci/Renderer/Camera/EditorCamera.h"
#include "Luci/Renderer/Camera/OrthographicCamera.h"
#include "Luci/Scene/Components.h"

namespace Luci {

	class Renderer2D {
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Primitives
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityId = -1);

		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& color = glm::vec4(1.0f), int entityId = -1);

		// Components
		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& srComponent, int entityId);

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

		static void DrawQuadFromTexIndex(const glm::mat4& transform, const glm::vec4& color, float texIndex, const glm::vec2* texCoords, int entityId = -1);
	};

}
