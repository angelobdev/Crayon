#pragma once

#include "Core.h"
#include "Logger.h"

extern Crayon::Application* Crayon::CreateApplication();

int main(int argc, char** argv)
{
	Crayon::Logger::Initialize();

	CRAYON_CORE_INFO("Welcome to Crayon Engine!");
	CRAYON_INFO("Sandbox created successfully!");

	auto* app = Crayon::CreateApplication();
	app->Run();
	return true;
}