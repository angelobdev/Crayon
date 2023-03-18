#include "Crayon.h"

class Sandbox : public Crayon::Application
{
public:
	Sandbox()
	{
		std::cout << "crypch.h works!\n";
	}

	~Sandbox() 
	{
	}

};

Crayon::Application* Crayon::CreateApplication()
{
	return new Sandbox();
}