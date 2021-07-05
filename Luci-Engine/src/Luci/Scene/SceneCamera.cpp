#include "lucipch.h"

#include "Luci/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Luci {

	SceneCamera::SceneCamera() {
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float verticalFov, float nearClip, float farClip) {
		m_ProjectionType = ProjectionType::Perspective;

		m_PerspectiveFov = verticalFov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
		m_ProjectionType = ProjectionType::Orthographic;

		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height) {
		float aspectRatio = (float)width / (float)height;
		if (m_AspectRatio != aspectRatio) {
			m_AspectRatio = aspectRatio;
			RecalculateProjection();
		}
	}

	void SceneCamera::RecalculateProjection() {
		if (m_ProjectionType == ProjectionType::Perspective) {
			m_ProjectionMatrix = glm::perspective(m_PerspectiveFov, m_AspectRatio,
				m_PerspectiveNear, m_PerspectiveFar);
		}
		else {
			float orthoTop = m_OrthographicSize * 0.5f;
			float orthoRight = orthoTop * m_AspectRatio;

			m_ProjectionMatrix = glm::ortho(-orthoRight, orthoRight, -orthoTop, orthoTop,
				m_OrthographicNear, m_OrthographicFar);
		}
	}

}
