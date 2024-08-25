#include "amoebapch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Amoeba {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AMOEBA_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		AMOEBA_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AMOEBA_ASSERT(status, "Failed to initialize Glad!");

		AMOEBA_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		AMOEBA_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		AMOEBA_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	};

	void OpenGLContext::SwapBuffers()
	{
		AMOEBA_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	};

};

