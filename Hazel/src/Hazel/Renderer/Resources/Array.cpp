#include "hzpch.h"
#include "Array.h"

#include "Hazel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLArray.h"

namespace Hazel {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		HZ_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

}
