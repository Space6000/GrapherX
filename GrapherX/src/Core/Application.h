#pragma once
#include <memory>
#include <iostream>
#include "Log.h"
#include "Window/Window.h"
#include "Window/WindowInput.h"
namespace Grapher
{
	class Application
	{
	public:
		Application();
		~Application();
		int Go();
		void Run();
	};

	Application* CreateApp();
}

