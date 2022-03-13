#include "typhpch.h"
#include "Typhoon/Renderer/Renderer2D.h"

#include "Typhoon/Renderer/RenderCommand.h"
#include "Typhoon/Renderer/Resources/Array.h"
#include "Typhoon/Renderer/Resources/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Typhoon
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		// Todo: texid
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t Maxindices = MaxQuads * 6;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture; // Create a default texture so flat colors do not mix with background textures

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.Maxindices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.Maxindices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.Maxindices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices; // can potentially be dangerous when working with a render thread and we delete early


		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		TYPH_PROFILE_FUNCTION();

	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
	}

	void Renderer2D::EndScene()
	{
		TYPH_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	// Normal quads
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.QuadVertexBufferPtr->Position = position; // Bottom left
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 0.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.f }; // Bottom right
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 0.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.f }; // Top right
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.f, 1.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.f }; // Top Left
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.f, 1.f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadIndexCount += 6;
		/*s_Data.TextureShader->SetFloat("u_TilingFactor", 1.f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * scale;

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor /* = 1.f */, const glm::vec4& tintColor /* = glm::vec4(1.f) */)
	{
		DrawQuad({ position.x, position.y, 0.f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor /* = 1.f */, const glm::vec4& tintColor /* = glm::vec4(1.f) */)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * scale;

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	// Rotatable versions
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float angle, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.f }, size, angle, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float angle, const glm::vec4& color)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), { 0.f, 0.f, 1.f });
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * rotation * scale;


		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float angle, const Ref<Texture2D>& texture, const float tilingFactor /* = 1.f */, const glm::vec4& tintColor /* = glm::vec4(1.f) */)
	{
		DrawRotatedQuad({ position.x, position.y, 0.f }, size, angle, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float angle, const Ref<Texture2D>& texture, const float tilingFactor /* = 1.f */, const glm::vec4& tintColor /* = glm::vec4(1.f) */)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), { 0.f, 0.f, 1.f });
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * rotation * scale;

		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

}