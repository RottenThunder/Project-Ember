#pragma once
#include "Core.h"
#include "Ember/Events/EventSystem.h"

namespace Ember
{
	class EMBER_API Layer
	{
	protected:
		std::string LayerName;
	public:
		Layer(const std::string& layerName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return LayerName; }
	};
}