#include "empch.h"
#include "OrthographicCameraController.h"
#include "Ember/Core/Input.h"
#include "Ember/Core/KeyCodes.h"

namespace Ember
{
	OrthographicCameraController::OrthographicCameraController(float_t aspectRatio, bool rotation)
		: AspectRatio(aspectRatio), Camera(-AspectRatio * ZoomLevel, AspectRatio* ZoomLevel, -ZoomLevel, ZoomLevel), Rotation(rotation)
	{

	}

	void OrthographicCameraController::OnUpdate(DeltaTime dt)
	{
		if (Input::IsKeyPressed(EM_KEY_A))
			CameraPosition.x -= CameraTranslationSpeed * dt;
		else if (Input::IsKeyPressed(EM_KEY_D))
			CameraPosition.x += CameraTranslationSpeed * dt;

		if (Input::IsKeyPressed(EM_KEY_W))
			CameraPosition.y += CameraTranslationSpeed * dt;
		else if (Input::IsKeyPressed(EM_KEY_S))
			CameraPosition.y -= CameraTranslationSpeed * dt;

		if (Rotation)
		{
			if (Input::IsKeyPressed(EM_KEY_Q))
				CameraRotation += CameraRotationSpeed * dt;
			if (Input::IsKeyPressed(EM_KEY_E))
				CameraRotation -= CameraRotationSpeed * dt;

			Camera.SetRotation(CameraRotation);
		}

		Camera.SetPosition(CameraPosition);

		CameraTranslationSpeed = ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EM_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(EM_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		ZoomLevel -= e.GetYOffset() * 0.25f;
		ZoomLevel = std::max(ZoomLevel, 0.25f);
		Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		Camera.SetProjection(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel);
		return false;
	}
}