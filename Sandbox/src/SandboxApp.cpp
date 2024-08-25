#include <Amoeba.h>
#include <Amoeba/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Amoeba::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Amoeba::Application* Amoeba::CreateApplication()
{
	return new Sandbox();
}