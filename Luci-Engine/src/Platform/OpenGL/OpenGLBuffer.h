#pragma once

#include "Luci/Renderer/Buffer.h"

namespace Luci {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(size_t size);
		OpenGLVertexBuffer(float* vertices, size_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		virtual void SetData(const void* data, uint32_t size) override;

		virtual size_t GetCount() const { return m_Size / sizeof(float); }

	private:
		uint32_t m_RendererID;
		size_t m_Size;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* inidices, size_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual size_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		size_t m_Count;
	};

}