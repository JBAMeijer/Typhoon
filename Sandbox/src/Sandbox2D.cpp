#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}

private:
	const char* m_Name;
	Fn& m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) {m_ProfileResults.push_back(profileResult); })

Sandbox2DLayer::Sandbox2DLayer()
	: Layer("Sandbox2DLayer"), m_CameraController(1280.f / 720.f)
{
}

void Sandbox2DLayer::OnAttach()
{
	m_CheckerBoardTexture = Typhoon::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2DLayer::OnDetach()
{
}

void Sandbox2DLayer::OnUpdate(Typhoon::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2DLayer::OnUpdate");

	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}
	// Render

	{
		PROFILE_SCOPE("Renderer Prep");
		Typhoon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Typhoon::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Draw Scene");
		Typhoon::Renderer2D::BeginScene(m_CameraController.GetCamera()); // Start the scene

		Typhoon::Renderer2D::DrawQuad({ 0.f, 0.f }, { 1.f, 1.f }, m_SquareColor);
		Typhoon::Renderer2D::DrawQuad({ 1.f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor, m_rotation);
		Typhoon::Renderer2D::DrawQuad({ 1.375f, 1.0f }, { 0.75f, 0.75f }, { 1.f, 0.f, 0.f, 1.f });
		Typhoon::Renderer2D::DrawQuad({ 2.10f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);
		Typhoon::Renderer2D::DrawQuad({ 2.65f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);
		Typhoon::Renderer2D::DrawQuad({ 3.20f, 1.0f }, { 0.5f, 0.5f }, m_SquareColor);

		Typhoon::Renderer2D::DrawQuad({ 0.f, 0.f, -0.1f }, { 10.f, 10.f }, m_CheckerBoardTexture);
		Typhoon::Renderer2D::EndScene(); // End the scene
	}
}

void Sandbox2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragFloat("rotation", &m_rotation, 1.f, 0.f, 360.f);

	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy(label, "%.3fms  ");
		strcat(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();

	ImGui::End();
}

void Sandbox2DLayer::OnEvent(Typhoon::Event& e)
{
	m_CameraController.OnEvent(e);
}
