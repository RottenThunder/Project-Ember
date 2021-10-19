#pragma once
#include "Application.h"
#include "Ember/Debug/Log.h"

extern Ember::Application* Ember::CreateApplication();

int main()
{
	Ember::Log::Init();
	EM_LOG_DEBUG("Log Initialized!");
	auto gameApp = Ember::CreateApplication();
	gameApp->Run();
	delete gameApp;
}