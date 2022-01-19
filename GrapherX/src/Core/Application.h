#pragma once
#include <memory>
#include <iostream>
#include "Log.h"
#include "Window/Window.h"
#include "Window/WindowInput.h"
#include "Graphic/ImGui/ImguiManager.h"
namespace Grapher
{
	class Application
	{
	public:
		Application();
		~Application();
		int Go();
		void Run();
	private:
		ImguiManager imguiManager;
	};

	Application* CreateApp();
}

