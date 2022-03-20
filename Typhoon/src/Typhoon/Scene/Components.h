#pragma once

#include <glm/glm.hpp>
#include "Typhoon/Camera/Camera.h"

namespace Typhoon
{
	struct TransformComponent
	{
		glm::mat4 com_Transform{ 1.f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 & transform)
			: com_Transform(transform) {}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 com_Color{ 1.f, 1.f, 1.f, 1.f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: com_Color(color) {}
	};

	struct TagComponent
	{
		std::string com_Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: com_Tag(tag) {}
	};

	struct CameraComponent
	{
		Camera com_Camera;
		bool com_Primary = true; // TODO: think about moving to scene

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			: com_Camera(projection) {}
	};
}