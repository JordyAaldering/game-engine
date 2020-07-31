#pragma once

#include <glm/glm.hpp>

namespace Luci {

	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(const glm::vec3& position);
		const glm::vec3& GetPosition() const { return m_Position; }

		void SetRotation(float rotation);
		float GetRotation() const { return m_ZRotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void RecalculateViewMatrix();

	private:
		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		float m_ZRotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};

}
