#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer"), m_CameraController(1280.f / 720.f, true)
{

}

void Sandbox2DLayer::OnAttach()
{
	m_SquareVA = Typhoon::VertexArray::Create();

	float squareVertices[3 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Typhoon::Ref<Typhoon::VertexBuffer> squareVB;
	squareVB.reset(Typhoon::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Typhoon::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Typhoon::Ref<Typhoon::IndexBuffer> squareIB;
	squareIB.reset(Typhoon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Typhoon::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Typhoon::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Typhoon::RenderCommand::Clear();

	Typhoon::Renderer::BeginScene(m_CameraController.GetCamera()); // Start the scene

	m_FlatColorShader->Bind();
	std::dynamic_pointer_cast<Typhoon::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Typhoon::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));

	Typhoon::Renderer::EndScene(); // End the scene
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Typhoon::Event& e)
{
	m_CameraController.OnEvent(e);
}
