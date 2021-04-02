#pragma once
#include "Typhoon/Core/Base.h"

#ifdef TYPH_PLATFORM_WINDOWS

extern Typhoon::Application* Typhoon::CreateApplication();

int main(int argc, char** argv)
{
	Typhoon::Log::Init();
	TYPH_CORE_WARN("Initialized Log!");
	int a = 5;
	TYPH_CLIENT_INFO("Hello! Var={0}", a);

	auto app = Typhoon::CreateApplication();
	app->Run();
	delete app;
}

#endif