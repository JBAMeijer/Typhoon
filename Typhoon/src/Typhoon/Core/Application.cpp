#include "typhpch.h"
#include "Typhoon/Core/Application.h"
#include "Typhoon/Core/Log.h"
#include "Typhoon/Core/Input.h"

#include "Typhoon/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Typhoon {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		TYPH_PROFILE_FUNCTION();

		TYPH_CORE_ASSERT(!s_Instance, "Application already exits");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(TYPH_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		TYPH_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}


	void Application::PushLayer(Layer* layer)
	{
		TYPH_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		TYPH_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		TYPH_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(TYPH_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(TYPH_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled) break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		TYPH_PROFILE_FUNCTION();

		while (m_Running)
		{
			TYPH_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); //Platform::GetTime
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) 
			{
				{
					TYPH_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			{
				TYPH_PROFILE_SCOPE("LayerStack OnImGuiRender");

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		TYPH_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}