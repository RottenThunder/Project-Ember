#pragma once
#include "Application.h"
#include "Ember/Debug/Log.h"

extern Ember::Application* Ember::CreateApplication();

int main()
{
	Ember::Log::Init();
	EM_LOG_DEBUG("Log Initialized!");
	EM_LOG_WARN("Initializing Ember Engine...");

	EM_PROFILE_BEGIN_SESSION("Startup", "Ember-Startup.json");
	auto gameApp = Ember::CreateApplication();
	EM_PROFILE_END_SESSION();

	EM_PROFILE_BEGIN_SESSION("Runtime", "Ember-Runtime.json");
	gameApp->Run();
	EM_PROFILE_END_SESSION();

	EM_PROFILE_BEGIN_SESSION("Shutdown", "Ember-Shutdown.json");
	delete gameApp;
	EM_PROFILE_END_SESSION();
}