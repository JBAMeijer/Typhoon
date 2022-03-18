#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer"), m_CameraController(1280.f / 720.f)
{
	m_VSyncEnabled = Typhoon::Application::Get().GetWindow().IsVSync();
	m_PreviousVSyncEnabled = m_VSyncEnabled;
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
	m_FrameTime = ts.GetMilliseconds();
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	Typhoon::Renderer2D::ResetStatistics();
	{
		TYPH_PROFILE_SCOPE("Renderer Prep");
		Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Typhoon::RenderCommand::Clear();
	}

	static float rotation = 0.f;
	rotation += ts * 20.f;
	
	{

		TYPH_PROFILE_SCOPE("Draw Scene");
		Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
		Typhoon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Typhoon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Typhoon::Renderer2D::DrawRotatedQuad({ 2.f, 1.5f }, { 0.5f, 1.5f }, rotation, { 0.2f, 0.8f, 0.8f, 1.0f });
		Typhoon::Renderer2D::DrawRotatedQuad({ 2.f, -0.5f }, { 0.5f, 1.5f }, m_rotation, { 0.2f, 0.8f, 0.2f, 1.0f });
		Typhoon::Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.f);
		//Typhoon::Renderer2D::DrawRotatedQuad({ -2.f, 0.f, 0.f }, { 1.f, 1.f }, 45.f, m_CheckerBoardTexture, 20.f);
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
				Typhoon::Renderer2D::DrawRotatedQuad({ x, y }, { 0.45f, 0.45f }, rotation * fabsf(x), color);
			}
		}
		Typhoon::Renderer2D::EndScene(); // End the scene
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	TYPH_PROFILE_FUNCTION();
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "")) Typhoon::Application::Get().Close();
			ImGui::Separator();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Docking settings"))
		{
			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; 
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoResize;
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0)) dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
			ImGui::Separator();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Settings");

	Typhoon::Renderer2D::Statistics stats = Typhoon::Renderer2D::GetStatistics();
	ImGui::Text("Render2D Statistics: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad count: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::Text("frametime (ms): %f", m_FrameTime);
	uint32_t fps = (uint32_t)(1000.f / m_FrameTime);
	ImGui::Text("FPS: %d", fps);	

	ImGui::Checkbox("VSync", &m_VSyncEnabled);
	if (m_PreviousVSyncEnabled != m_VSyncEnabled)
	{
		Typhoon::Application::Get().GetWindow().SetVSync(m_VSyncEnabled);
		m_PreviousVSyncEnabled = m_VSyncEnabled;
	}

	ImGui::DragFloat("rotation", &m_rotation, 1.f, 0.f, 360.f);

	uint32_t textureID = m_CheckerBoardTexture->GetRendererID();
	ImGui::Image((ImTextureID)textureID, { 256.f, 256.f });

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
