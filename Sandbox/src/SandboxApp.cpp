#include <Typhoon.h>
#include <Typhoon/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Typhoon::Application
{
public:
	Sandbox()
	{
		TYPH_PROFILE_FUNCTION();
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2DLayer());
	}
	~Sandbox()
	{

	}
};

Typhoon::Application* Typhoon::CreateApplication()
{
	return new Sandbox();
}