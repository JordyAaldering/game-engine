#pragma once

#include "Core.h"

namespace Luci {

	class Input {
	public:
		// Key input
		static bool IsKeyPressed(int keyCode);

		// Mouse input
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
