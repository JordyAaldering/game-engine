#pragma once

#include "Luci/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Luci {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() = default;

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}
