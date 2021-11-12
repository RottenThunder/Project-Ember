#pragma once
#include "empch.h"
#include "Event.h"

namespace Ember
{
	class EMBER_API KeyEvent : public Event
	{
	protected:
		uint16_t KeyCode;

		KeyEvent(uint16_t keycode)
			: KeyCode(keycode) {}
	public:
		inline uint16_t GetKeyCode() const { return KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class EMBER_API KeyPressedEvent : public KeyEvent
	{
	private:
		uint64_t RepeatCount;
	public:
		KeyPressedEvent(uint16_t keycode, uint64_t repeatCount)
			: KeyEvent(keycode), RepeatCount(repeatCount) {}

		inline uint64_t GetRepeatCount() const { return RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << KeyCode << " (" << RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class EMBER_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(uint16_t keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class EMBER_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(uint16_t keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}