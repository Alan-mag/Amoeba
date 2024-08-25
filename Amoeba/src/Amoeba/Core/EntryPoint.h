#pragma once

#ifdef AMOEBA_PLATFORM_WINDOWS

extern Amoeba::Application* Amoeba::CreateApplication();

int main(int argc, char** argv) {
	Amoeba::Log::Init();
	AMOEBA_CORE_INFO("Amoeba Engine\n");
	auto app = Amoeba::CreateApplication();
	app->Run();
	delete app;
}

#endif