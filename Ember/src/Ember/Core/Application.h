#pragma once
#include "Core.h"

namespace Ember
{
	class EMBER_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}