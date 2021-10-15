#pragma once
#include "Application.h"
#include "Ember/Debug/Log.h"

extern Ember::Application* Ember::CreateApplication();

int main()
{
	Ember::Log::Init();
	int a = 9;
	EM_LOG_TRACE("Welcome to Ember Engine!");
	EM_LOG_DEBUG("This is a Debug Message!");
	EM_LOG_INFO("This is an Info Message! var = {0}", a);
	EM_LOG_WARN("This is a Warning Message!");
	EM_LOG_ERROR("This is an Error Message!");
	EM_LOG_FATAL("This is a Fatal Message!");
	auto gameApp = Ember::CreateApplication();
	gameApp->Run();
	delete gameApp;
}