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
		float_t ZoomLevel;
		float_t CameraTranslationSpeed = 1.0f;
		float_t CameraRotationSpeed = 180.0f;
		glm::vec3 CameraPosition = { 0.0f, 0.0f, 0.0f };
		float_t CameraRotation = 0.0f;
		OrthographicCamera Camera;
	public:
		//The aspect ratio has to be expressed as the width divided by the height, for example: 16.0f / 9.0f for a 16:9 Ratio
		OrthographicCameraController(float_t aspectRatio, float_t zoomLevel = 1.0f, bool rotation = false);

		OrthographicCamera& GetCamera() { return Camera; }
		const OrthographicCamera& GetCamera() const { return Camera; }

		void OnUpdate(DeltaTime dt);
		void OnEvent(Event& e);

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	};
}