#include "Crayon.h"

class Sandbox : public Crayon::Application
{
public:
	Sandbox() : Application("Sandbox", 800, 600)
	{
		
	}

	~Sandbox() 
	{
	}

};

Crayon::Application* Crayon::CreateApplication()
{
	return new Sandbox();
}