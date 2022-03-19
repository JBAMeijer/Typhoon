#pragma once
#include <Typhoon.h>
#include <Typhoon/Events/KeyEvent.h>

namespace Typhoon
{

	class ConvectionLayer : public Layer
	{
	public:
		ConvectionLayer();
		virtual ~ConvectionLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		OrthographicCameraController m_CameraController;
	
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Texture2D> m_CheckerBoardTexture;

		Ref<FrameBuffer> m_FrameBuffer;

		float m_rotation = 0.f;
		float m_FrameTime = 0.f;
		bool m_VSyncEnabled = false;
		bool m_PreviousVSyncEnabled = m_VSyncEnabled;
	};

}
