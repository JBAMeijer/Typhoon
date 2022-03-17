#pragma once
#include <Typhoon.h>
#include <Typhoon/Events/KeyEvent.h>

class Sandbox2DLayer : public Typhoon::Layer
{
public:
	Sandbox2DLayer();
	virtual ~Sandbox2DLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Typhoon::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Typhoon::Event& e) override;
private:
	bool OnKeyPressed(Typhoon::KeyPressedEvent& e);
private:
	Typhoon::OrthographicCameraController m_CameraController;
	
	Typhoon::Ref<Typhoon::VertexArray> m_SquareVA;
	Typhoon::Ref<Typhoon::Shader> m_FlatColorShader;
	Typhoon::Ref<Typhoon::Texture2D> m_CheckerBoardTexture;
	Typhoon::Ref<Typhoon::Texture2D> m_ShmupSpriteSheetTiles;
	Typhoon::Ref<Typhoon::Texture2D> m_ShmupSpriteSheetShips;
	Typhoon::Ref<Typhoon::SubTexture2D> m_ShmupShip;

	float m_rotation = 0.f;
	float m_FrameTime = 0.f;
	bool m_VSyncEnabled = false;
	bool m_PreviousVSyncEnabled = m_VSyncEnabled;
};