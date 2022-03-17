#pragma once

#include "Typhoon/Renderer/OrthographicCamera.h"

#include "Typhoon/Renderer/Resources/Texture.h"
#include "Typhoon/Renderer/Resources/SubTexture.h"

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
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color); // vec3 for z indexing for rendering objects in layers
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f)); // vec3 for z indexing for rendering objects in layers
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f)); // vec3 for z indexing for rendering objects in layers
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f)); // vec3 for z indexing for rendering objects in layers


		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotationInDegrees, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotationInDegrees, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotationInDegrees, const Ref<Texture2D>& texture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotationInDegrees, const Ref<Texture2D>& texture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotationInDegrees, const Ref<SubTexture2D>& subTexture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotationInDegrees, const Ref<SubTexture2D>& subTexture, const float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4(1.f));


		// Statistics
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics GetStatistics();
		static void ResetStatistics();

	private:
		static void Flush();
		static void FlushAndReset();
	};
}
