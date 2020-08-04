#include "lucipch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Luci {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) {
		LUCI_CORE_ASSERT(windowHandle, "Window handle is null.");
	}

	void OpenGLContext::Init() {
		LUCI_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LUCI_CORE_ASSERT(status, "Failed to initialize Glad.");

		LUCI_CORE_INFO("OpenGL renderer\n\tVendor: {0}\n\tRenderer: {1}\n\tVersion: {2}",
			glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

		#ifdef LUCI_ENABLE_ASSERTS
			int versionMajor, versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			LUCI_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Luci requires at least OpenGL version 4.5.");
		#endif
	}

	void OpenGLContext::SwapBuffers() {
		LUCI_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}
