#include "lucipch.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Luci {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create() {
		switch (s_API) {
			case API::None:
				LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
				return nullptr;
			case API::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

}
