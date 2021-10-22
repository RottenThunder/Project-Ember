#pragma once
#include "Application.h"
#include "Ember/Debug/Log.h"

extern Ember::Application* Ember::CreateApplication();

int main()
{
	Ember::Log::Init();
	EM_LOG_DEBUG("Log Initialized!");
	EM_LOG_WARN("Initializing Ember Engine...");
	// Mass Initialization Here!!!
	auto gameApp = Ember::CreateApplication();
	gameApp->Run();
	delete gameApp;
}