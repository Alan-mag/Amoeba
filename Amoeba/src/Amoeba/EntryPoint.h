#pragma once

#ifdef AMOEBA_PLATFORM_WINDOWS

extern Amoeba::Application* Amoeba::CreateApplication();

int main(int argc, char** argv) {
	printf("Amoeba Engine\n");
	auto app = Amoeba::CreateApplication();
	app->Run();
	delete app;
}

#endif