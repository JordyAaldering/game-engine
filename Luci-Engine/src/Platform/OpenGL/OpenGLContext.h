#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Renderer/GraphicsContext.h"

// Forward declare
struct GLFWwindow;

namespace Luci {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext() = default;

		virtual void Initialize() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};

}
