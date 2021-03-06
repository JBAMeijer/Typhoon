#pragma once

#include "Typhoon/Core/Base.h"
#include "Typhoon/Core/Timestep.h"
#include "Typhoon/Events/Event.h"

namespace Typhoon {

	class Layer
	{
	public:
		Layer(const std::string& name = "layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}

