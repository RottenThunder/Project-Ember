#pragma once
#include <stdint.h>
#include "Core.h"

namespace Ember
{
	class EMBER_API Input
	{
	private:
		static Input* Instance;
	protected:
		virtual bool IsKeyPressedImpl(uint16_t keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(uint16_t button) = 0;
		virtual std::pair<float_t, float_t> GetMousePositionImpl() = 0;
		virtual float_t GetMouseXImpl() = 0;
		virtual float_t GetMouseYImpl() = 0;
	public:
		inline static bool IsKeyPressed(uint16_t keycode) { return Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(uint16_t button) { return Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float_t, float_t> GetMousePosition() { return Instance->GetMousePositionImpl(); }
		inline static float_t GetMouseX() { return Instance->GetMouseXImpl(); }
		inline static float_t GetMouseY() { return Instance->GetMouseYImpl(); }
	};
}