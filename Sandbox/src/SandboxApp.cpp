#include <Amoeba.h>

#include "imgui/imgui.h"

class ExampleLayer : public Amoeba::Layer 
{
public:
	ExampleLayer()
		: Layer("Example")

	{

	}

	void OnUpdate() override
	{
		// AMOEBA_INFO("ExampleLayer::Update");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Amoeba::Event& event) override
	{
		if (event.GetEventType() == Amoeba::EventType::KeyPressed) 
		{
			Amoeba::KeyPressedEvent& e = (Amoeba::KeyPressedEvent&)event;
			if (e.GetKeyCode() == AMOEBA_KEY_TAB)
				AMOEBA_TRACE("Tab key is pressed (event)!");
			AMOEBA_TRACE("{0}", (char)e.GetKeyCode());
		}
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