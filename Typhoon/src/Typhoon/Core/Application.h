#pragma once

#include "Typhoon/Core/Base.h"

#include "Window.h"
#include "Typhoon/Core/LayerStack.h"
#include "Typhoon/Events/Event.h"
#include "Typhoon/Events/ApplicationEvent.h"

#include "Typhoon/ImGui/ImGuiLayer.h"

#include "Typhoon/Core/Timestep.h"

namespace Typhoon {

	class TYPHOON_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();

}
