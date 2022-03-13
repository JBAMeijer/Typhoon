#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer"), m_CameraController(1280.f / 720.f)
{
}

void Sandbox2DLayer::OnAttach()
{
	TYPH_PROFILE_FUNCTION();

	m_CheckerBoardTexture = Typhoon::Texture2D::Create("assets/textures/Checkerboard64.png");
}

void Sandbox2DLayer::OnDetach()
{
	TYPH_PROFILE_FUNCTION();

}

void Sandbox2DLayer::OnUpdate(Typhoon::Timestep ts)
{
	TYPH_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	{
		TYPH_PROFILE_SCOPE("Renderer Prep");
		Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Typhoon::RenderCommand::Clear();
	}

	{
		TYPH_PROFILE_SCOPE("Draw Scene");
		Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
		Typhoon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Typhoon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Typhoon::Renderer2D::DrawRotatedQuad({ 2.f, -0.5f }, { 0.5f, 1.5f }, m_rotation, { 0.2f, 0.8f, 0.2f, 1.0f });
		//Typhoon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerBoardTexture, 5.f, {0.5f, 0.5f, 0.5f, 1.f});
		Typhoon::Renderer2D::EndScene(); // End the scene
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	TYPH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragFloat("rotation", &m_rotation, 1.f, 0.f, 360.f);
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Typhoon::Event& e)
{
	m_CameraController.OnEvent(e);

	Typhoon::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Typhoon::KeyPressedEvent>(TYPH_BIND_EVENT_FN(Sandbox2DLayer::OnKeyPressed));
}

bool Sandbox2DLayer::OnKeyPressed(Typhoon::KeyPressedEvent& e)
{
	TYPH_CLIENT_INFO("Keycode from Sandbox2DLayer: {0}", e.GetKeyCode());
	return false;
}
