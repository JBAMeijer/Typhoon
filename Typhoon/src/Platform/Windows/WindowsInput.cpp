#include "typhpch.h"
#include "Platform/Windows/WindowsInput.h"

#include "Typhoon/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Typhoon {
	
#define GET_NATIVE_WINDOW(x) static_cast<x*>(Application::Get().GetWindow().GetNativeWindow())

	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode mouseButtonCode)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButtonCode));
		return state == GLFW_PRESS;
	}

	/*std::pair<bool, std::pair<float, float>> WindowsInput::HasMouseMovedImpl(float origX, float origY)
	{
		double xpos = 0, ypos = 0;
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		glfwGetCursorPos(window, &xpos, &ypos);

		if (origX != (float)xpos || origY != (float)ypos)
			return std::make_pair(true, std::make_pair((float)xpos, (float)ypos));
		else
			return std::make_pair(false, std::make_pair(NULL, NULL));
	}*/

	bool WindowsInput::HasMouseMovedImpl(float origX, float origY)
	{
		auto[x, y] = GetMousePositionImpl();

		if (origX != x || origY != y)
			return true;
		else
			return false;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		double xpos = 0.0, ypos = 0.0;
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

}