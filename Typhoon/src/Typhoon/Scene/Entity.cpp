#include "typhpch.h"
#include "Entity.h"

namespace Typhoon
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

}