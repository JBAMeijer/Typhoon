#pragma once

#include <utility>
#include "Hazel/Core/Base.h"

namespace Hazel {

	class HAZEL_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		//inline static std::pair<bool, std::pair<float, float>> HasMouseMoved(float origX, float origY) { return s_Instance->HasMouseMovedImpl(origX, origY); }
		
		inline static bool HasMouseMoved(float origX, float origY) { return s_Instance->HasMouseMovedImpl(origX, origY); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		//virtual std::pair<bool, std::pair<float, float>> HasMouseMovedImpl(float origX, float origY) = 0;
		
		virtual bool HasMouseMovedImpl(float origX, float origY) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};

}