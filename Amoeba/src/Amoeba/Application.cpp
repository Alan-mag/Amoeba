#include "amoebapch.h"
#include "Application.h"

#include "Amoeba/Events/ApplicationEvent.h"
#include "Amoeba/Log.h"

namespace Amoeba {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			AMOEBA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			AMOEBA_TRACE(e);
		}
		while (true);
	}

}