#pragma once

#include "Luci/Renderer/Camera/OrthographicCamera.h"
#include "Luci/Core/Timestep.h"

#include "Luci/Events/ApplicationEvent.h"
#include "Luci/Events/MouseEvent.h"

namespace Luci {

	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep timestep);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
		float GetZoomLevel() { return m_ZoomLevel; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraZoomSpeed = 0.25f;
		float m_CameraRotationSpeed = 180.0f;
	};

}
