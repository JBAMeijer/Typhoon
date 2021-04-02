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
	

	Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene

	Typhoon::Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, m_SquareColor);
	Typhoon::Renderer2D::DrawQuad({ 1.f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor, m_rotation);
	Typhoon::Renderer2D::DrawQuad({ 1.375f, 1.0f }, { 0.75f, 0.75f }, {1.f, 0.f, 0.f, 1.f});
	Typhoon::Renderer2D::DrawQuad({ 2.10f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);
	Typhoon::Renderer2D::DrawQuad({ 2.65f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);
	Typhoon::Renderer2D::DrawQuad({ 3.20f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);


	Typhoon::Renderer2D::EndScene(); // End the scene

	// m_FlatColorShader->Bind();
	// std::dynamic_pointer_cast<Typhoon::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragFloat("rotation", &m_rotation, 1.f, 0.f, 360.f);
	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Typhoon::Event& e)
{
	m_CameraController.OnEvent(e);
}
