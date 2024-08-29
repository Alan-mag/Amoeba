#pragma once

#ifdef AMOEBA_PLATFORM_WINDOWS

extern Amoeba::Application* Amoeba::CreateApplication();

int main(int argc, char** argv) {
	Amoeba::Log::Init();
	// AMOEBA_PROFILE_BEGIN_SESSION("Startup", "AmoebaProfile-Startup.json");
	auto app = Amoeba::CreateApplication();
	// AMOEBA_PROFILE_END_SESSION();

	// AMOEBA_PROFILE_BEGIN_SESSION("Runtime", "AmoebaProfile-Runtime.json");
	app->Run();
	// AMOEBA_PROFILE_END_SESSION();

	// AMOEBA_PROFILE_BEGIN_SESSION("Startup", "AmoebaProfile-Shutdown.json");
	delete app;
	// AMOEBA_PROFILE_END_SESSION();
}

#endif