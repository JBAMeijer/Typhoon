#include "typhpch.h"
#include "GraphicsContext.h"

#include "Typhoon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Typhoon
{

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    TYPH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		TYPH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}