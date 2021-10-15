#pragma once
#include "Application.h"

extern Ember::Application* Ember::CreateApplication();

int main()
{
	auto gameApp = Ember::CreateApplication();
	gameApp->Run();
	delete gameApp;
}