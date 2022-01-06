#include "GrapherX.h"
#include <iostream>


class Sandbox : public Grapher::Application {

public:
	Sandbox() 
	{
	}

	~Sandbox() 
	{

	}
};

Grapher::Application* Grapher::CreateApp() 
{
	return new Sandbox;
}
