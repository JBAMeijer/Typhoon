#include "ConvectionLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Typhoon
{

	ConvectionLayer::ConvectionLayer()
		: Layer("Sandbox2DLayer"), m_CameraController(1280.f / 720.f)
	{
		m_VSyncEnabled = Application::Get().GetWindow().IsVSync();
		m_PreviousVSyncEnabled = m_VSyncEnabled;
	}

	void ConvectionLayer::OnAttach()
	{
		TYPH_PROFILE_FUNCTION();

		m_CheckerBoardTexture = Texture2D::Create("assets/textures/Checkerboard64.png");

		FrameBufferSpecification frameBufferSpecification{ 1280, 720 };
		m_FrameBuffer = FrameBuffer::Create(frameBufferSpecification);
	}

	void ConvectionLayer::OnDetach()
	{
		TYPH_PROFILE_FUNCTION();

	}

	void ConvectionLayer::OnUpdate(Timestep ts)
	{
		TYPH_PROFILE_FUNCTION();
		m_FrameTime = ts.GetMilliseconds();

		// Resize
		if (FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_FrameBuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		// Update
		if(m_ViewportFocused)
			m_CameraController.OnUpdate(ts);
	
		// Render
		Renderer2D::ResetStatistics();
		{
			TYPH_PROFILE_SCOPE("Renderer Prep");
			m_FrameBuffer->Bind();
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}

		static float rotation = 0.f;
		rotation += ts * 20.f;
	
		{

			TYPH_PROFILE_SCOPE("Draw Scene");
			Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
			Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Renderer2D::DrawRotatedQuad({ 2.f, 1.5f }, { 0.5f, 1.5f }, rotation, { 0.2f, 0.8f, 0.8f, 1.0f });
			Renderer2D::DrawRotatedQuad({ 2.f, -0.5f }, { 0.5f, 1.5f }, m_rotation, { 0.2f, 0.8f, 0.2f, 1.0f });
			Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 20.0f, 20.0f }, m_CheckerBoardTexture, 10.f);
			//Renderer2D::DrawRotatedQuad({ -2.f, 0.f, 0.f }, { 1.f, 1.f }, 45.f, m_CheckerBoardTexture, 20.f);
			Renderer2D::EndScene(); // End the scene

		}
		{
			TYPH_PROFILE_SCOPE("Draw multiple colored quads scene");
			Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene
			for (float y = -4.75f; y < 5.25f; y += 0.5f)
			{
				for (float x = -4.75f; x < 5.25f; x += 0.5f)
				{
					glm::vec4 color{ (x + 5.f) / 10.f, 0.4f, (y + 5.f) / 10.f, 0.5f };
					Renderer2D::DrawRotatedQuad({ x, y }, { 0.45f, 0.45f }, rotation * fabsf(x), color);
				}
			}
			Renderer2D::EndScene(); // End the scene
			m_FrameBuffer->Unbind();
		}
	}

	void ConvectionLayer::OnImGuiRender()
	{
		TYPH_PROFILE_FUNCTION();
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit", "")) Application::Get().Close();
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

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		
		ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewPortSize.x, viewPortSize.y };

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((ImTextureID)textureID, viewPortSize, { 0, 1 }, { 1, 0 });

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("Settings");

		Renderer2D::Statistics stats = Renderer2D::GetStatistics();
		ImGui::Text("Render2D Statistics: ");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad count: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::Text("Frametime (ms): %f", m_FrameTime);
		uint32_t fps = (uint32_t)(1000.f / m_FrameTime);
		ImGui::Text("FPS: %d", fps);	

		ImGui::Checkbox("VSync", &m_VSyncEnabled);
		if (m_PreviousVSyncEnabled != m_VSyncEnabled)
		{
			Application::Get().GetWindow().SetVSync(m_VSyncEnabled);
			m_PreviousVSyncEnabled = m_VSyncEnabled;
		}

		ImGui::DragFloat("rotation", &m_rotation, 1.f, 0.f, 360.f);

		ImGui::End();
	}

	void ConvectionLayer::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(TYPH_BIND_EVENT_FN(ConvectionLayer::OnKeyPressed));
	}

	bool ConvectionLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		TYPH_CLIENT_INFO("Keycode from Sandbox2DLayer: {0}", e.GetKeyCode());
		return false;
	}

}
