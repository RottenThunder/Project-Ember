#pragma once
#include "Ember/Core/Core.h"
#include "OrthographicCamera.h"
#include "Ember/Core/DeltaTime.h"
#include "Ember/Events/EventSystem.h"

namespace Ember
{
	class EMBER_API OrthographicCameraController
	{
	private:
		float_t AspectRatio;
		bool Rotation;
		float_t ZoomLevel = 1.0f;
		float_t CameraTranslationSpeed = 1.0f;
		float_t CameraRotationSpeed = 180.0f;
		glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
		float_t CameraRotation = 0.0f;
		OrthographicCamera Camera;
	public:
		OrthographicCameraController(float_t aspectRatio, bool rotation = false);

		OrthographicCamera& GetCamera() { return Camera; }
		const OrthographicCamera& GetCamera() const { return Camera; }

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	};
}