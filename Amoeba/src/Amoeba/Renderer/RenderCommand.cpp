#include "amoebapch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Amoeba {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

};