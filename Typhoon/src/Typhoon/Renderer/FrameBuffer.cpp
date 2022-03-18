#include "typhpch.h"
#include "FrameBuffer.h"

#include "Typhoon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Typhoon
{

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())	
		{
		case RendererAPI::API::None:    TYPH_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFrameBuffer>(spec);
		}

		TYPH_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}