#include "lucipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Luci {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
