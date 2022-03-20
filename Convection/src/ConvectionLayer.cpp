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

		m_ActiveScene = CreateRef<Scene>();

		auto square = m_ActiveScene->CreateEntity("Colorable square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.f, 1.f, 0.f, 1.f });


		m_SquareEntity = square;
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
		m_FrameBuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
		

		Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene

		// Update scene
		m_ActiveScene->OnUpdate(ts);
		
		Renderer2D::EndScene(); // End the scene
		
		m_FrameBuffer->Unbind();
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
		
		if (m_SquareEntity)
		{
			ImGui::Separator();
			auto& tag = m_SquareEntity.GetComponent<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
			ImGui::Separator();

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
