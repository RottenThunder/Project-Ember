#pragma once
#include "Ember/Core/Layer.h"

namespace Ember
{
	class EMBER_API ImGuiLayer : public Ember::Layer
	{
	private:
		float_t Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};
}