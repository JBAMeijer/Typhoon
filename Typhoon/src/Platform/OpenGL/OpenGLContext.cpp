#include "typhpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
		TYPH_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TYPH_CORE_ASSERT(status, "Failed to initialize Glad!");

		TYPH_CORE_INFO("OpenGL info:");
		TYPH_CORE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		TYPH_CORE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		TYPH_CORE_INFO(" Version: {0}", glGetString(GL_VERSION));

		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		TYPH_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Typhoon requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		TYPH_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}