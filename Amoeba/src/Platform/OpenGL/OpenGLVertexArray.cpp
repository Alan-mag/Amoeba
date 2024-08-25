#include "amoebapch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Amoeba {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Amoeba::ShaderDataType::Float:    return GL_FLOAT;
		case Amoeba::ShaderDataType::Float2:   return GL_FLOAT;
		case Amoeba::ShaderDataType::Float3:   return GL_FLOAT;
		case Amoeba::ShaderDataType::Float4:   return GL_FLOAT;
		case Amoeba::ShaderDataType::Mat3:     return GL_FLOAT;
		case Amoeba::ShaderDataType::Mat4:     return GL_FLOAT;
		case Amoeba::ShaderDataType::Int:      return GL_INT;
		case Amoeba::ShaderDataType::Int2:     return GL_INT;
		case Amoeba::ShaderDataType::Int3:     return GL_INT;
		case Amoeba::ShaderDataType::Int4:     return GL_INT;
		case Amoeba::ShaderDataType::Bool:     return GL_BOOL;
		}

		AMOEBA_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		AMOEBA_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		AMOEBA_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		AMOEBA_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		AMOEBA_PROFILE_FUNCTION();

		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		AMOEBA_PROFILE_FUNCTION();

		AMOEBA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		AMOEBA_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

};