#pragma once
#include "Core.h"
#include "DeltaTime.h"
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
		virtual void OnUpdate(DeltaTime DT) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return LayerName; }
	};
}