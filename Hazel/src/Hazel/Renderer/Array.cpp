#include "hzpch.h"
#include "Array.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLArray.h"

namespace Hazel {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

}
