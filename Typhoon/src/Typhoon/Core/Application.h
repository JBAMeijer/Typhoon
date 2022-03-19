#pragma once

#include "Typhoon/Core/Base.h"

#include "Typhoon/Core/Window.h"
#include "Typhoon/Core/LayerStack.h"
#include "Typhoon/Core/Timestep.h"

#include "Typhoon/Events/Event.h"
#include "Typhoon/Events/ApplicationEvent.h"

#include "Typhoon/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Typhoon {

	class Application
	{
	public:
		Application(const std::string& name = "Typhoon App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be defined in a client
	Application* CreateApplication();

}
