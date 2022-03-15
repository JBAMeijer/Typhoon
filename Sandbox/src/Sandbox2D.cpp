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
	m_Start = ts.GetMilliseconds();
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	Typhoon::Renderer2D::ResetStatistics();
	{
		TYPH_PROFILE_SCOPE("Renderer Prep");
		Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Typhoon::RenderCommand::Clear();
	}

	{
		static float rotation = 0.f;
		rotation += ts * 20.f;

		TYPH_PROFILE_SCOPE("Draw Scene");
		Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
		Typhoon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Typhoon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Typhoon::Renderer2D::DrawRotatedQuad({ 2.f, 1.5f }, { 0.5f, 1.5f }, rotation, { 0.2f, 0.8f, 0.8f, 1.0f });
		Typhoon::Renderer2D::DrawRotatedQuad({ 2.f, -0.5f }, { 0.5f, 1.5f }, m_rotation, { 0.2f, 0.8f, 0.2f, 1.0f });
		Typhoon::Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.f);
		Typhoon::Renderer2D::DrawRotatedQuad({ -2.f, 0.f, 0.f }, { 1.f, 1.f }, 45.f, m_CheckerBoardTexture, 20.f);
		Typhoon::Renderer2D::EndScene(); // End the scene

	}
	{
		TYPH_PROFILE_SCOPE("Draw multiple colored quads scene");
		Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
		for (float y = -4.75f; y < 5.25f; y += 0.5f)
		{
			for (float x = -4.75f; x < 5.25f; x += 0.5f)
			{
				glm::vec4 color{ (x + 5.f) / 10.f, 0.4f, (y + 5.f) / 10.f, 0.5f };
				Typhoon::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Typhoon::Renderer2D::EndScene(); // End the scene
		m_Stop = ts.GetMilliseconds();
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	TYPH_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	Typhoon::Renderer2D::Statistics stats = Typhoon::Renderer2D::GetStatistics();
	ImGui::Text("Render2D Statistics: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::Text("Timestep start: %d", m_Start);
	ImGui::Text("Timestep stop: %d", m_Stop);


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
