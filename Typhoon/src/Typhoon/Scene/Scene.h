#pragma once

#include <EnTT/entt.h>

namespace Typhoon
{

	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;

	};

}


