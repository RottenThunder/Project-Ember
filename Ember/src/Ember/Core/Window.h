#pragma once
#include "empch.h"
#include "Ember/Core/Core.h"
#include "Ember/Events/Event.h"

namespace Ember
{
	struct WindowProperties
	{
		std::string Title;
		uint16_t Width;
		uint16_t Height;

		WindowProperties(const std::string& title = "Ember Engine", uint16_t width = 1280, uint16_t height = 720)
		{
			Title = title;
			Width = width;
			Height = height;
		}
	};

	// Interface representing a Graphical Window
	class EMBER_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual uint16_t GetWidth() const = 0;
		virtual uint16_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void OnUpdate() = 0;

		static Window* Create(const WindowProperties& props = WindowProperties());
	};

}