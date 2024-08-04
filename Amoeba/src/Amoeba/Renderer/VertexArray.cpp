#include "amoebapch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Amoeba {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    AMOEBA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		AMOEBA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}