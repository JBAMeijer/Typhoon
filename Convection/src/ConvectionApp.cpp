#include <Typhoon.h>
#include <Typhoon/Core/EntryPoint.h>

#include "ConvectionLayer.h"

namespace Typhoon
{
	class Convection : public Application
	{
	public:
		Convection() : Application("Convection")
		{
			TYPH_PROFILE_FUNCTION();
			//PushLayer(new ExampleLayer());
			PushLayer(new ConvectionLayer());
		}
		~Convection()
		{ 

		}
	};

	Application* CreateApplication()
	{
		return new Convection();
	}

}
