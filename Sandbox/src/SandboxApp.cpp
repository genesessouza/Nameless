#include "Nameless.h"

class ExampleLayer : public Nameless::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{		
	}

	void OnEvent(Nameless::Event& event) override
	{
		NMLS_INFO("{0}", event.ToString());

		if (event.GetEventType() == Nameless::EventType::KeyPressed)
		{
			Nameless::KeyPressedEvent& e = (Nameless::KeyPressedEvent&)event;
			NMLS_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Nameless::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Nameless::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Nameless::Application* Nameless::CreateApplication()
{
	return new Sandbox();
}