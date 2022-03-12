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

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.f };
	float m_rotation = 0.f;
};