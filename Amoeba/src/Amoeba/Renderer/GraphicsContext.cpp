#include "amoebapch.h"
#include "Amoeba/Renderer/GraphicsContext.h"

#include "Amoeba/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Amoeba {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AMOEBA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		AMOEBA_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}