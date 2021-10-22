#pragma once
#include "empch.h"
#include "Event.h"

namespace Ember
{
	class EMBER_API MouseMovedEvent : public Event
	{
	private:
		float_t MouseX;
		float_t MouseY;
	public:
		MouseMovedEvent(float_t mouseX, float_t mouseY)
		{
			MouseX = mouseX;
			MouseY = mouseY;
		}

		inline float_t GetX() const { return MouseX; }
		inline float_t GetY() const { return MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << MouseX << ", " << MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class EMBER_API MouseScrolledEvent : public Event
	{
	private:
		float_t XOffset;
		float_t YOffset;
	public:
		MouseScrolledEvent(float_t xOffset, float_t yOffset)
		{
			XOffset = xOffset;
			YOffset = yOffset;
		}

		inline float_t GetXOffset() const { return XOffset; }
		inline float_t GetYOffset() const { return YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class EMBER_API MouseButtonEvent : public Event
	{
	protected:
		uint16_t Button;

		MouseButtonEvent(uint16_t button)
		{
			Button = button;
		}
	public:
		inline uint16_t GetMouseButton() const { return Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class EMBER_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(uint16_t button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class EMBER_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(uint16_t button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}