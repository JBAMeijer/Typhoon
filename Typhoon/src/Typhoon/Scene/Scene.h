#pragma once

#include <EnTT/entt.h>

#include "Typhoon/Core/Timestep.h"

namespace Typhoon
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		
		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;

	};

}


