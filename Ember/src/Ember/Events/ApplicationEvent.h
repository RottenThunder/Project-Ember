#pragma once
#include "empch.h"
#include "Event.h"

namespace Ember
{
	class EMBER_API WindowMovedEvent : public Event
	{
	private:
		uint16_t X;
		uint16_t Y;
	public:
		WindowMovedEvent(uint16_t x, uint16_t y)
			: X(x), Y(y) {}

		inline uint16_t GetX() const { return X; }
		inline uint16_t GetY() const { return Y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent: " << X << ", " << Y;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EMBER_API WindowResizeEvent : public Event
	{
	private:
		uint16_t Width;
		uint16_t Height;
	public:
		WindowResizeEvent(uint16_t width, uint16_t height)
			: Width(width), Height(height) {}

		inline uint16_t GetWidth() const { return Width; }
		inline uint16_t GetHeight() const { return Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << Width << ", " << Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EMBER_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EMBER_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EMBER_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class EMBER_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}