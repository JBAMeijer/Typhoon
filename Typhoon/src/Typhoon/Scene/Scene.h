#pragma once

#include <EnTT/entt.h>

#include "Typhoon/Core/Timestep.h"

namespace Typhoon
{

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();
		
		// TEMP
		entt::registry& Reg() { return m_Registry; }
		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

	};

}


