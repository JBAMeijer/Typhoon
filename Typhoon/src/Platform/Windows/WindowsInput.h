#pragma once

#include "Typhoon/Core/Input.h"

namespace Typhoon {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		//virtual std::pair<bool, std::pair<float, float>> HasMouseMovedImpl(float origX, float origY) override;

		virtual bool HasMouseMovedImpl(float origX, float origY) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}
