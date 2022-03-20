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
		Ref<Texture2D> m_CheckerBoardTexture;
		Ref<Scene> m_ActiveScene;
		Ref<FrameBuffer> m_FrameBuffer;

		Entity m_SquareEntity;
		Entity m_CameraEntity;
		Entity m_SecondCameraEntity;

		bool m_PrimaryCamera = true;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = {1280.f, 720.f};

		float m_rotation = 0.f;
		float m_FrameTime = 0.f;
		bool m_VSyncEnabled = false;
		bool m_PreviousVSyncEnabled = m_VSyncEnabled;
	};

}
