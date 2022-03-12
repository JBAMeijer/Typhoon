#pragma once
#include "Typhoon/Renderer/OrthographicCamera.h"
#include "Typhoon/Core/Timestep.h"

#include "Typhoon/Events/ApplicationEvent.h"
#include "Typhoon/Events/MouseEvent.h"

namespace Typhoon {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline OrthographicCamera& GetCamera() { return m_Camera; }
		inline const OrthographicCamera& GetCamera() const { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.f, 0.f, 0.f };
		float m_CameraRotation = 0.f; // In degrees in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.f, m_CameraRotationSpeed = 180.f;
	};

}