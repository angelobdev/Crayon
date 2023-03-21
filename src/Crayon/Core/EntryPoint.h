#pragma once

#include "Base.h"
#include "Logger.h"

extern Crayon::Application* Crayon::CreateApplication();

int main(int argc, char** argv)
{
	Crayon::Logger::Initialize();

	CRAYON_CORE_INFO("Welcome to Crayon Engine!");

	auto* app = Crayon::CreateApplication();
	app->Run();

	CRAYON_CORE_INFO("Bye! <3");
	std::cin.get();
	return EXIT_SUCCESS;
}