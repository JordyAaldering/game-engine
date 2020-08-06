#include "lucipch.h"
#include "Framebuffer.h"

#include "Luci/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Luci {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& specification) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(specification);
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

}
