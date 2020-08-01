#pragma once

namespace Luci {

	enum class ShaderDataType {
		None = 0,
		Bool,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Bool:	 return 1;
			case ShaderDataType::Int:	 return 4;
			case ShaderDataType::Int2:	 return 8;
			case ShaderDataType::Int3:	 return 12;
			case ShaderDataType::Int4:	 return 16;
			case ShaderDataType::Float:	 return 4;
			case ShaderDataType::Float2: return 8;
			case ShaderDataType::Float3: return 12;
			case ShaderDataType::Float4: return 16;
			case ShaderDataType::Mat3:	 return 36;
			case ShaderDataType::Mat4:	 return 64;
		}

		LUCI_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size, Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const {
			switch (Type) {
				case ShaderDataType::Bool:	 return 1;
				case ShaderDataType::Int:	 return 1;
				case ShaderDataType::Int2:	 return 2;
				case ShaderDataType::Int3:	 return 3;
				case ShaderDataType::Int4:	 return 4;
				case ShaderDataType::Float:	 return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3:	 return 9;
				case ShaderDataType::Mat4:	 return 16;
			}

			LUCI_CORE_ASSERT(false, "Unknown ShaderDataType.");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) {
			CalculateOffsets();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

		void CalculateOffsets() {
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
	};

	class VertexBuffer {
	public:
		static Ref<VertexBuffer> Create(float* vertices, size_t size);
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual size_t GetCount() const = 0;
	};

	class IndexBuffer {
	public:
		static Ref<IndexBuffer> Create(uint32_t* indices, size_t size);
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual size_t GetCount() const = 0;
	};

}
