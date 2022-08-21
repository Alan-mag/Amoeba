#include "amoebapch.h"
#include "Application.h"

#include "Amoeba/Events/ApplicationEvent.h"
#include "Amoeba/Log.h"

#include <GLFW/glfw3.h>

namespace Amoeba {

	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() 
	{

	}

	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(0, 1, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}