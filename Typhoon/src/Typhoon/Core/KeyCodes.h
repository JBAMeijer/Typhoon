#pragma once

namespace Typhoon
{
	enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define TYPH_KEY_SPACE           ::Typhoon::KeyCode::Space
#define TYPH_KEY_APOSTROPHE      ::Typhoon::KeyCode::Apostrophe    /* ' */
#define TYPH_KEY_COMMA           ::Typhoon::KeyCode::Comma         /* , */
#define TYPH_KEY_MINUS           ::Typhoon::KeyCode::Minus         /* - */
#define TYPH_KEY_PERIOD          ::Typhoon::KeyCode::Period        /* . */
#define TYPH_KEY_SLASH           ::Typhoon::KeyCode::Slash         /* / */
#define TYPH_KEY_0               ::Typhoon::KeyCode::D0
#define TYPH_KEY_1               ::Typhoon::KeyCode::D1
#define TYPH_KEY_2               ::Typhoon::KeyCode::D2
#define TYPH_KEY_3               ::Typhoon::KeyCode::D3
#define TYPH_KEY_4               ::Typhoon::KeyCode::D4
#define TYPH_KEY_5               ::Typhoon::KeyCode::D5
#define TYPH_KEY_6               ::Typhoon::KeyCode::D6
#define TYPH_KEY_7               ::Typhoon::KeyCode::D7
#define TYPH_KEY_8               ::Typhoon::KeyCode::D8
#define TYPH_KEY_9               ::Typhoon::KeyCode::D9
#define TYPH_KEY_SEMICOLON       ::Typhoon::KeyCode::Semicolon     /* ; */
#define TYPH_KEY_EQUAL           ::Typhoon::KeyCode::Equal         /* = */
#define TYPH_KEY_A               ::Typhoon::KeyCode::A
#define TYPH_KEY_B               ::Typhoon::KeyCode::B
#define TYPH_KEY_C               ::Typhoon::KeyCode::C
#define TYPH_KEY_D               ::Typhoon::KeyCode::D
#define TYPH_KEY_E               ::Typhoon::KeyCode::E
#define TYPH_KEY_F               ::Typhoon::KeyCode::F
#define TYPH_KEY_G               ::Typhoon::KeyCode::G
#define TYPH_KEY_H               ::Typhoon::KeyCode::H
#define TYPH_KEY_I               ::Typhoon::KeyCode::I
#define TYPH_KEY_J               ::Typhoon::KeyCode::J
#define TYPH_KEY_K               ::Typhoon::KeyCode::K
#define TYPH_KEY_L               ::Typhoon::KeyCode::L
#define TYPH_KEY_M               ::Typhoon::KeyCode::M
#define TYPH_KEY_N               ::Typhoon::KeyCode::N
#define TYPH_KEY_O               ::Typhoon::KeyCode::O
#define TYPH_KEY_P               ::Typhoon::KeyCode::P
#define TYPH_KEY_Q               ::Typhoon::KeyCode::Q
#define TYPH_KEY_R               ::Typhoon::KeyCode::R
#define TYPH_KEY_S               ::Typhoon::KeyCode::S
#define TYPH_KEY_T               ::Typhoon::KeyCode::T
#define TYPH_KEY_U               ::Typhoon::KeyCode::U
#define TYPH_KEY_V               ::Typhoon::KeyCode::V
#define TYPH_KEY_W               ::Typhoon::KeyCode::W
#define TYPH_KEY_X               ::Typhoon::KeyCode::X
#define TYPH_KEY_Y               ::Typhoon::KeyCode::Y
#define TYPH_KEY_Z               ::Typhoon::KeyCode::Z
#define TYPH_KEY_LEFT_BRACKET    ::Typhoon::KeyCode::LeftBracket   /* [ */
#define TYPH_KEY_BACKSLASH       ::Typhoon::KeyCode::Backslash     /* \ */
#define TYPH_KEY_RIGHT_BRACKET   ::Typhoon::KeyCode::RightBracket  /* ] */
#define TYPH_KEY_GRAVE_ACCENT    ::Typhoon::KeyCode::GraveAccent   /* ` */
#define TYPH_KEY_WORLD_1         ::Typhoon::KeyCode::World1        /* non-US #1 */
#define TYPH_KEY_WORLD_2         ::Typhoon::KeyCode::World2        /* non-US #2 */

/* Function keys */
#define TYPH_KEY_ESCAPE          ::Typhoon::KeyCode::Escape
#define TYPH_KEY_ENTER           ::Typhoon::KeyCode::Enter
#define TYPH_KEY_TAB             ::Typhoon::KeyCode::Tab
#define TYPH_KEY_BACKSPACE       ::Typhoon::KeyCode::Backspace
#define TYPH_KEY_INSERT          ::Typhoon::KeyCode::Insert
#define TYPH_KEY_DELETE          ::Typhoon::KeyCode::Delete
#define TYPH_KEY_RIGHT           ::Typhoon::KeyCode::Right
#define TYPH_KEY_LEFT            ::Typhoon::KeyCode::Left
#define TYPH_KEY_DOWN            ::Typhoon::KeyCode::Down
#define TYPH_KEY_UP              ::Typhoon::KeyCode::Up
#define TYPH_KEY_PAGE_UP         ::Typhoon::KeyCode::PageUp
#define TYPH_KEY_PAGE_DOWN       ::Typhoon::KeyCode::PageDown
#define TYPH_KEY_HOME            ::Typhoon::KeyCode::Home
#define TYPH_KEY_END             ::Typhoon::KeyCode::End
#define TYPH_KEY_CAPS_LOCK       ::Typhoon::KeyCode::CapsLock
#define TYPH_KEY_SCROLL_LOCK     ::Typhoon::KeyCode::ScrollLock
#define TYPH_KEY_NUM_LOCK        ::Typhoon::KeyCode::NumLock
#define TYPH_KEY_PRINT_SCREEN    ::Typhoon::KeyCode::PrintScreen
#define TYPH_KEY_PAUSE           ::Typhoon::KeyCode::Pause
#define TYPH_KEY_F1              ::Typhoon::KeyCode::F1
#define TYPH_KEY_F2              ::Typhoon::KeyCode::F2
#define TYPH_KEY_F3              ::Typhoon::KeyCode::F3
#define TYPH_KEY_F4              ::Typhoon::KeyCode::F4
#define TYPH_KEY_F5              ::Typhoon::KeyCode::F5
#define TYPH_KEY_F6              ::Typhoon::KeyCode::F6
#define TYPH_KEY_F7              ::Typhoon::KeyCode::F7
#define TYPH_KEY_F8              ::Typhoon::KeyCode::F8
#define TYPH_KEY_F9              ::Typhoon::KeyCode::F9
#define TYPH_KEY_F10             ::Typhoon::KeyCode::F10
#define TYPH_KEY_F11             ::Typhoon::KeyCode::F11
#define TYPH_KEY_F12             ::Typhoon::KeyCode::F12
#define TYPH_KEY_F13             ::Typhoon::KeyCode::F13
#define TYPH_KEY_F14             ::Typhoon::KeyCode::F14
#define TYPH_KEY_F15             ::Typhoon::KeyCode::F15
#define TYPH_KEY_F16             ::Typhoon::KeyCode::F16
#define TYPH_KEY_F17             ::Typhoon::KeyCode::F17
#define TYPH_KEY_F18             ::Typhoon::KeyCode::F18
#define TYPH_KEY_F19             ::Typhoon::KeyCode::F19
#define TYPH_KEY_F20             ::Typhoon::KeyCode::F20
#define TYPH_KEY_F21             ::Typhoon::KeyCode::F21
#define TYPH_KEY_F22             ::Typhoon::KeyCode::F22
#define TYPH_KEY_F23             ::Typhoon::KeyCode::F23
#define TYPH_KEY_F24             ::Typhoon::KeyCode::F24
#define TYPH_KEY_F25             ::Typhoon::KeyCode::F25

/* Keypad */
#define TYPH_KEY_KP_0            ::Typhoon::KeyCode::KP0
#define TYPH_KEY_KP_1            ::Typhoon::KeyCode::KP1
#define TYPH_KEY_KP_2            ::Typhoon::KeyCode::KP2
#define TYPH_KEY_KP_3            ::Typhoon::KeyCode::KP3
#define TYPH_KEY_KP_4            ::Typhoon::KeyCode::KP4
#define TYPH_KEY_KP_5            ::Typhoon::KeyCode::KP5
#define TYPH_KEY_KP_6            ::Typhoon::KeyCode::KP6
#define TYPH_KEY_KP_7            ::Typhoon::KeyCode::KP7
#define TYPH_KEY_KP_8            ::Typhoon::KeyCode::KP8
#define TYPH_KEY_KP_9            ::Typhoon::KeyCode::KP9
#define TYPH_KEY_KP_DECIMAL      ::Typhoon::KeyCode::KPDecimal
#define TYPH_KEY_KP_DIVIDE       ::Typhoon::KeyCode::KPDivide
#define TYPH_KEY_KP_MULTIPLY     ::Typhoon::KeyCode::KPMultiply
#define TYPH_KEY_KP_SUBTRACT     ::Typhoon::KeyCode::KPSubtract
#define TYPH_KEY_KP_ADD          ::Typhoon::KeyCode::KPAdd
#define TYPH_KEY_KP_ENTER        ::Typhoon::KeyCode::KPEnter
#define TYPH_KEY_KP_EQUAL        ::Typhoon::KeyCode::KPEqual

#define TYPH_KEY_LEFT_SHIFT      ::Typhoon::KeyCode::LeftShift
#define TYPH_KEY_LEFT_CONTROL    ::Typhoon::KeyCode::LeftControl
#define TYPH_KEY_LEFT_ALT        ::Typhoon::KeyCode::LeftAlt
#define TYPH_KEY_LEFT_SUPER      ::Typhoon::KeyCode::LeftSuper
#define TYPH_KEY_RIGHT_SHIFT     ::Typhoon::KeyCode::RightShift
#define TYPH_KEY_RIGHT_CONTROL   ::Typhoon::KeyCode::RightControl
#define TYPH_KEY_RIGHT_ALT       ::Typhoon::KeyCode::RightAlt
#define TYPH_KEY_RIGHT_SUPER     ::Typhoon::KeyCode::RightSuper
#define TYPH_KEY_MENU            ::Typhoon::KeyCode::Menu