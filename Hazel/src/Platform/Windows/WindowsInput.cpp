#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel {
	
#define GET_NATIVE_WINDOW(x) static_cast<x*>(Application::Get().GetWindow().GetNativeWindow())

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_RELEASE;
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