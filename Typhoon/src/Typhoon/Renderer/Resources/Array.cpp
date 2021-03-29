#include "typhpch.h"
#include "Array.h"

#include "Typhoon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLArray.h"

namespace Typhoon {
	
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		TYPH_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		}

		TYPH_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

}
