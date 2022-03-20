#include "typhpch.h"

#include "Typhoon/Scene/Scene.h"
#include "Typhoon/Scene/Entity.h"
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

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Empty_Entity" : name;

		return entity;
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