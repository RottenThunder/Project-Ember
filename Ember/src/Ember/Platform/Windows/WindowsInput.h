#pragma once
#include "Ember/Core/Input.h"

namespace Ember
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(uint16_t keycode) override;
		virtual bool IsMouseButtonPressedImpl(uint16_t button) override;
		virtual std::pair<float_t, float_t> GetMousePositionImpl() override;
		virtual float_t GetMouseXImpl() override;
		virtual float_t GetMouseYImpl() override;
	};
}