#pragma once

#include "Luci/Layer.h"
#include "Luci/Events/ApplicationEvent.h"
#include "Luci/Events/KeyEvent.h"
#include "Luci/Events/MouseEvent.h"

namespace Luci {

	class LUCI_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
	};

}
