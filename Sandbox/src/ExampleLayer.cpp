#include "ExampleLayer.h"

#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>


ExampleLayer::ExampleLayer()
	: Layer("Example"), m_CameraController(1280.f / 720.f, true)
{
	m_VertexArray = Typhoon::VertexArray::Create();

	float vertices[3 * 7] =
	{
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};

	Typhoon::Ref<Typhoon::VertexBuffer> m_VertexBuffer = Typhoon::VertexBuffer::Create(vertices, sizeof(vertices));
	Typhoon::BufferLayout layout = {
		{ Typhoon::ShaderDataType::Float3, "a_Position" },
		{ Typhoon::ShaderDataType::Float4, "a_Color" }
	};
	m_VertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Typhoon::Ref<Typhoon::IndexBuffer> m_IndexBuffer = Typhoon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_SquareVA = Typhoon::VertexArray::Create();

	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f, 0.f, 0.f,
		 0.5f, -0.5f, 0.0f, 1.f, 0.f,
		 0.5f,  0.5f, 0.0f, 1.f, 1.f,
		-0.5f,  0.5f, 0.0f, 0.f, 1.f
	};

	Typhoon::Ref<Typhoon::VertexBuffer> squareVB = Typhoon::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	squareVB->SetLayout({
		{ Typhoon::ShaderDataType::Float3, "a_Position" },
		{ Typhoon::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Typhoon::Ref<Typhoon::IndexBuffer> squareIB = Typhoon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

	m_Shader = Typhoon::Shader::Create("Triangle Shader", vertexSrc, fragmentSrc);

	std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = Typhoon::Shader::Create("SquareShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

	Typhoon::Ref<Typhoon::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Typhoon::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TyphoonLogoTexture = Typhoon::Texture2D::Create("assets/textures/TyphoonLogo.png");


	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(Typhoon::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Typhoon::RenderCommand::Clear();

	Typhoon::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);


	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
			glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
			Typhoon::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Typhoon::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

	m_TyphoonLogoTexture->Bind();
	Typhoon::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

	//Triangle
	/*Typhoon::Renderer::Submit(m_Shader, m_VertexArray);*/

	Typhoon::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(Typhoon::Event& e)
{
	m_CameraController.OnEvent(e);
}