#include "lucipch.h"
#include "GraphicsContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Luci {

	Scope<GraphicsContext> GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

}
