#pragma once

namespace Typhoon
{
	enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2,
	};

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}

}


#define TYPH_MOUSE_BUTTON_1      ::Typhoon::MouseCode::Button0
#define TYPH_MOUSE_BUTTON_2      ::Typhoon::MouseCode::Button1
#define TYPH_MOUSE_BUTTON_3      ::Typhoon::MouseCode::Button2
#define TYPH_MOUSE_BUTTON_4      ::Typhoon::MouseCode::Button3
#define TYPH_MOUSE_BUTTON_5      ::Typhoon::MouseCode::Button4
#define TYPH_MOUSE_BUTTON_6      ::Typhoon::MouseCode::Button5
#define TYPH_MOUSE_BUTTON_7      ::Typhoon::MouseCode::Button6
#define TYPH_MOUSE_BUTTON_8      ::Typhoon::MouseCode::Button7
#define TYPH_MOUSE_BUTTON_LAST   ::Typhoon::MouseCode::ButtonLast
#define TYPH_MOUSE_BUTTON_LEFT   ::Typhoon::MouseCode::ButtonLeft
#define TYPH_MOUSE_BUTTON_RIGHT  ::Typhoon::MouseCode::ButtonRight
#define TYPH_MOUSE_BUTTON_MIDDLE ::Typhoon::MouseCode::ButtonMiddle