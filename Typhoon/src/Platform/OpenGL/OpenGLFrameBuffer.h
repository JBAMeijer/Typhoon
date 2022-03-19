#pragma once

#include "Typhoon/Renderer/FrameBuffer.h"

namespace Typhoon
{

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();
		
		void ReCreateInvalidatedState();
		
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; };
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; };
		
		virtual void Bind() override;
		virtual void Unbind() override; 

		void Resize(const uint32_t width, const uint32_t height) override;

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;
	};

}

