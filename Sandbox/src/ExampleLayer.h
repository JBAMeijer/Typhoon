#pragma once
#include <Typhoon.h>

class ExampleLayer : public Typhoon::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Typhoon::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Typhoon::Event& e) override;

private:
	Typhoon::ShaderLibrary m_ShaderLibrary;
	Typhoon::Ref<Typhoon::Shader> m_Shader;
	Typhoon::Ref<Typhoon::VertexArray> m_VertexArray;

	Typhoon::Ref<Typhoon::Shader> m_FlatColorShader;
	Typhoon::Ref<Typhoon::VertexArray> m_SquareVA;

	Typhoon::Ref<Typhoon::Texture2D> m_Texture, m_TyphoonLogoTexture;

	Typhoon::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};