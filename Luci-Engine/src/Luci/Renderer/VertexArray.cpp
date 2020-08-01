#include "lucipch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Luci {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

}
