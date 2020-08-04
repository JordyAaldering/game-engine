#include "lucipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Luci {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
