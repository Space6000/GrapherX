#pragma once
#include <memory>
#include <iostream>
#include "Log.h"
#include "Events/Event.h"
#include "Window/WindowsWindow.h"

namespace Grapher
{
	class Application
	{
	public:
		Application();
		~Application();
		int Go();
		void Run();
		void OnEvent(Event& e);
	private:

		std::unique_ptr<WindowsWindow> window = std::make_unique<WindowsWindow>(L"GrapherX", 1024, 768);
	};

	Application* CreateApp();
}

