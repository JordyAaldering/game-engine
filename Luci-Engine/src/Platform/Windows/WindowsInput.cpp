#include "lucipch.h"

#include "Luci/Core/Input/Input.h"
#include "Luci/Core/Input/KeyCodes.h"
#include "Luci/Core/Input/MouseCodes.h"
#include "Luci/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Luci {

	/*
	 * Key input
	 */

	bool Input::IsKeyPressed(KeyCode key) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, static_cast<int>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	/*
	 * Mouse input
	 */

	bool Input::IsMouseButtonPressed(MouseCode button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	float Input::GetMouseX() {
		auto [xPos, _yPos] = GetMousePosition();
		return xPos;
	}

	float Input::GetMouseY() {
		auto [_xPos, yPos] = GetMousePosition();
		return yPos;
	}

}
