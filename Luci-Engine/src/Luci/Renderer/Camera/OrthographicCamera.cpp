#include "lucipch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Luci {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top)), m_ViewMatrix(1.0f) {
		LUCI_PROFILE_FUNCTION();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		LUCI_PROFILE_FUNCTION();
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position) {
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation) {
		m_ZRotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		LUCI_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_ZRotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
