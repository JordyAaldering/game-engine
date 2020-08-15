#pragma once

#include "Luci/Core/Core.h"

#include "Luci/Core/Layer.h"
#include "Luci/Events/ApplicationEvent.h"
#include "Luci/Events/KeyEvent.h"
#include "Luci/Events/MouseEvent.h"

namespace Luci {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
	};

}
