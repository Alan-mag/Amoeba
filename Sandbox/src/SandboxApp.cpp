#include <Amoeba.h>

class Sandbox : public Amoeba::Application {
	public:
		Sandbox() {

		}

		~Sandbox() {

		}
};

Amoeba::Application* Amoeba::CreateApplication() {
	return new Sandbox();
}