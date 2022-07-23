#pragma once

#include "Core.h"

namespace Amoeba {

	class AMOEBA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}

