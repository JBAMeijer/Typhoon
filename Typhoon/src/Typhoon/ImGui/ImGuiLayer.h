#pragma once

#include "Typhoon/Core/Layer.h"

#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/MouseEvent.h"
#include "Typhoon/Events/KeyEvent.h"


namespace Typhoon {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}