#include "lucipch.h"
#include "OrthographicCameraController.h"

#include "Luci/Core/Input.h"
#include "Luci/Core/KeyCodes.h"

namespace Luci {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {}

	void OrthographicCameraController::OnUpdate(Timestep timestep) {
		LUCI_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(LUCI_KEY_A)) {
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		} else if (Input::IsKeyPressed(LUCI_KEY_D)) {
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(LUCI_KEY_W)) {
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		} else if (Input::IsKeyPressed(LUCI_KEY_S)) {
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		if (m_Rotation) {
			if (Input::IsKeyPressed(LUCI_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			} else if (Input::IsKeyPressed(LUCI_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * timestep;
			}

			if (m_CameraRotation > 180.0f) {
				m_CameraRotation -= 360.0f;
			} else if (m_CameraRotation <= -180.0f) {
				m_CameraRotation += 360.0f;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& event) {
		LUCI_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(LUCI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LUCI_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
		LUCI_PROFILE_FUNCTION();

		m_ZoomLevel -= event.GetYOffset() * m_CameraZoomSpeed;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.01f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
		LUCI_PROFILE_FUNCTION();

		m_AspectRatio = (float) event.GetWidth() / event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
