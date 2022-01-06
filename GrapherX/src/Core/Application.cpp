#include "Application.h"
#include "KeyCode.h"
namespace Grapher
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	int Application::Go()
	{
		Window app(L"GrapherX", 1024, 768);
		while (true)
		{
			// process all messages pending, but to not block for new messages
			if (const auto ecode = Window::ProcessMessage())
			{
				// if return optional has value, means we're quitting so return exit code
				return *ecode;
			
			}
			if (Grapher::WindowInput::IsKeyPressed(GP_KEY_SPACE))
			{
				GP_CORE_INFO("Space Key is pressed..");
			}
			app.Gfx().EndFrame();
		}

		return 0;
	}

	void Application::Run()
	{
		try
		{
			Go();
		}
		catch(const GrapherXException& e)
		{
			GP_CORE_ERROR(e.what());
			MessageBox(nullptr, e.dis(), NULL, MB_OK | MB_ICONEXCLAMATION);
		}
		catch (const std::exception& e)
		{
			GP_CORE_ERROR(e.what());
			MessageBox(nullptr, nullptr, L"Standerd Exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (...)
		{
			GP_CORE_ERROR("Unknown Exception");
			MessageBox(nullptr, L"No Details Found", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}
}