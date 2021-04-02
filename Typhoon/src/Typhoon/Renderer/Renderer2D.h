#pragma once

#include "Typhoon/Renderer/OrthographicCamera.h"
#include "Typhoon/Renderer/Resources/Texture.h"

namespace Typhoon
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float angle = 0.f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float angle = 0.f); // vec3 for z indexing for rendering objects in layers
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float angle = 0.f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float angle = 0.f); // vec3 for z indexing for rendering objects in layers

	};
}