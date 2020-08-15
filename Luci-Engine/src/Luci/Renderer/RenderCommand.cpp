#include "lucipch.h"

#include "Luci/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Luci {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
