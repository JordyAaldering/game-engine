#pragma once

#include "Luci/Core/Core.h"

namespace Luci {

	enum class FramebufferTextureFormat {
		None = 0,

		// color
		RGBA8,
		RED_INTEGER,

		// depth/stencil
		DEPTH24STENCIL8,

		// defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification {
		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
		// TODO: filtering and wrapping

		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}
	};

	struct FramebufferAttachmentSpecification {
		std::vector< FramebufferTextureSpecification> Attachments;

		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments) :
			Attachments(attachments) {}
	};

	struct FramebufferSpecification {
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		static Ref<Framebuffer> Create(const FramebufferSpecification& specification);
		virtual ~Framebuffer() = default;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;
		virtual uint32_t GetDepthAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;
	};

}
