#pragma once

#include "Core.h"

namespace Crayon
{
	class Application 
	{
	private:

	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication(); // To be defined in client
}