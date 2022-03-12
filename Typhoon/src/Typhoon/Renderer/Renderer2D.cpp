#include "typhpch.h"
#include "Typhoon/Renderer/Renderer2D.h"

#include "Typhoon/Renderer/RenderCommand.h"
#include "Typhoon/Renderer/Resources/Array.h"
#include "Typhoon/Renderer/Resources/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Typhoon
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture; // Standaard een witte texture toevoegen, zodat losse kleuren niet sampelen met andere textures.
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		TYPH_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		TYPH_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
		TYPH_PROFILE_FUNCTION();

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const float angle /*= 0.f*/)
	{
		DrawQuad({ position.x, position.y, 0.f }, size, color, angle);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const float angle /*= 0.f*/)
	{
		TYPH_PROFILE_FUNCTION();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), {size.x, size.y, 1.f});
		glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), { 0.f, 0.f, 1.f });
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * rotation * scale;

		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->WhiteTexture->Bind();

		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float angle /*= 0.f*/)
	{
		DrawQuad({ position.x, position.y, 0.f }, size, texture, angle);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float angle /*= 0.f*/)
	{
		TYPH_PROFILE_FUNCTION();

		s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.f));
		texture->Bind();

		glm::mat4 scale = glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		glm::mat4 rotation = glm::rotate(glm::mat4(1.f), glm::radians(angle), { 0.f, 0.f, 1.f });
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * rotation * scale;

		s_Data->TextureShader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}