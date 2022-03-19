#pragma once

//#include <utility>
#include "Typhoon/Core/Base.h"
#include "Typhoon/Core/KeyCodes.h"
#include "Typhoon/Core/MouseCodes.h"


namespace Typhoon {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		
		static bool HasMouseMoved(float origX, float origY);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}