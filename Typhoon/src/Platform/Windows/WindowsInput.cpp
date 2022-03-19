#include "typhpch.h"
#include "Typhoon/Core/Input.h"

#include "Typhoon/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Typhoon {
	
#define GET_NATIVE_WINDOW(x) static_cast<x*>(Application::Get().GetWindow().GetNativeWindow())

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode mouseButtonCode)
	{
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(mouseButtonCode));
		return state == GLFW_PRESS;
	}

	bool Input::HasMouseMoved(float origX, float origY)
	{
		auto[x, y] = GetMousePosition();

		if (origX != x || origY != y)
			return true;
		else
			return false;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		double xpos = 0.0, ypos = 0.0;
		auto window = GET_NATIVE_WINDOW(GLFWwindow);
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		auto[x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		auto[x, y] = GetMousePosition();
		return y;
	}

}