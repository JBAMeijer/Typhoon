#pragma once
#include "Typhoon/Core/Base.h"

#ifdef TYPH_PLATFORM_WINDOWS

extern Typhoon::Application* Typhoon::CreateApplication();

int main(int argc, char** argv)
{
	Typhoon::Log::Init();

	TYPH_PROFILE_BEGIN_SESSION("Startup", "TyphoonProfile-Startup.json");
	auto app = Typhoon::CreateApplication();
	TYPH_PROFILE_END_SESSION();
	
	TYPH_PROFILE_BEGIN_SESSION("Runtime", "TyphoonProfile-Runtime.json");
	app->Run();
	TYPH_PROFILE_END_SESSION();

	TYPH_PROFILE_BEGIN_SESSION("Shutdown", "TyphoonProfile-Shutdown.json");
	delete app;
	TYPH_PROFILE_END_SESSION();

}

#endif