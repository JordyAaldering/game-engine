#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Core/Input/KeyCodes.h"
#include "Luci/Core/Input/MouseCodes.h"

namespace Luci {

	class Input {
	protected:
		Input() = default;

	public:
		~Input() = default;

		// Key input
		static bool IsKeyPressed(KeyCode key);

		// Mouse input
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
