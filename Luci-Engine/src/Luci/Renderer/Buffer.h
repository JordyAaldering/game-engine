#pragma once

namespace Luci {

	class VertexBuffer {
	public:
		static VertexBuffer* Create(float* vertices, size_t size);
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};

	class IndexBuffer {
	public:
		static IndexBuffer* Create(uint32_t* indices, size_t size);
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};

}
