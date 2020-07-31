#include "lucipch.h"
#include "OrthographicCameraController.h"

#include "Luci/Core/Input.h"
#include "Luci/Core/KeyCodes.h"

namespace Luci {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

	}

	void OrthographicCameraController::OnUpdate(Timestep timestep) {
		if (Input::IsKeyPressed(LUCI_KEY_A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;
		} else if (Input::IsKeyPressed(LUCI_KEY_D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * timestep;
		}

		if (Input::IsKeyPressed(LUCI_KEY_W)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * timestep;
		} else if (Input::IsKeyPressed(LUCI_KEY_S)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;

		if (m_Rotation) {
			if (Input::IsKeyPressed(LUCI_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			} else if (Input::IsKeyPressed(LUCI_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * timestep;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(LUCI_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LUCI_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
		m_ZoomLevel -= event.GetYOffset() * m_CameraZoomSpeed;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.01f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
		m_AspectRatio -= (float) event.GetWidth() / event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}
