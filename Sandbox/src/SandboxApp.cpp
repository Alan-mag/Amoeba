#include <Amoeba.h>

class ExampleLayer : public Amoeba::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")

	{

	}

	void OnUpdate() override
	{
		AMOEBA_INFO("ExampleLayer::Update");
	}

	void OnEvent(Amoeba::Event& event) override
	{
		AMOEBA_TRACE("{0}", event);
	}
};

class Sandbox : public Amoeba::Application {
	public:
		Sandbox() 
		{
			PushLayer(new ExampleLayer());
		}

		~Sandbox() 
		{

		}
};

Amoeba::Application* Amoeba::CreateApplication() {
	return new Sandbox();
}