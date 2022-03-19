#pragma once

#include "Typhoon/Core/Base.h"

namespace Typhoon
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		//FrameBufferFormat format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;
		
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(const uint32_t width, const uint32_t height) = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};

}



