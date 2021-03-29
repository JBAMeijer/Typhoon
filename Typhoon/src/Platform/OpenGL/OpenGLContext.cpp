#include "typhpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Typhoon {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TYPH_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TYPH_CORE_ASSERT(status, "Failed to initialize Glad!");

		TYPH_CORE_INFO("OpenGL info:");
		TYPH_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		TYPH_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		TYPH_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}