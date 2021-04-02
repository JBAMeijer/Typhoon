#include "typhpch.h"
#include "Buffer.h"

#include "Typhoon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Typhoon {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	TYPH_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		TYPH_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	TYPH_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		TYPH_CORE_ASSERT(false, "Unknown RendererAPI!");

		return nullptr;
	}

}