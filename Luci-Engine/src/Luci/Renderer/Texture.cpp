#include "lucipch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Luci {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(width, height);
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:
				LUCI_CORE_ASSERT(false, "RendererAPI::None is not supported.");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLTexture2D>(filepath);
		}

		LUCI_CORE_ASSERT(false, "Unknown RendererAPI value.");
		return nullptr;
	}

}
