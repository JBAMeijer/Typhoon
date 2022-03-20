#include "typhpch.h"
#include "Typhoon/Scene/Scene.h"

#include "Typhoon/Scene/Components.h"
#include "Typhoon/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Typhoon
{

	static void Math(const glm::mat4& transform)
	{

	}

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		//m_Registry.clear();
	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.Transform, sprite.Color);
		}

	}

}