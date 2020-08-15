#include "lucipch.h"

#include "Luci/Scene/SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Luci {

	SceneCamera::SceneCamera() {
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip) {
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

	void SceneCamera::SetOrthographicSize(float size) {
		m_OrthographicSize = size;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection() {
		float orthoTop = m_OrthographicSize * 0.5f;
		float orthoRight = orthoTop * m_AspectRatio;

		m_ProjectionMatrix = glm::ortho(-orthoRight, orthoRight, -orthoTop, orthoTop,
			m_OrthographicNear, m_OrthographicFar);
	}

}
