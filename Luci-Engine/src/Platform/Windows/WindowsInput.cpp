#include "lucipch.h"
#include "WindowsInput.h"
#include "Luci/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Luci {

	Scope <Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl() {
		auto [xPos, _] = GetMousePosImpl();
		return xPos;
	}

	float WindowsInput::GetMouseYImpl() {
		auto [_, yPos] = GetMousePosImpl();
		return yPos;
	}

}
