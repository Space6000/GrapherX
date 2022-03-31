#include "Application.h"

namespace Grapher
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this, std::placeholders::_1)

	Application::Application()
	{
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	int Application::Go()
	{
		while (true)
		{
			// process all messages pending, but to not block for new messages
			if (const auto ecode = window->ProcessMessage())
			{
				// if return optional has value, means we're quitting so return exit code
				return *ecode;
			}
			window->Gfx().EndFrame();
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
	void Application::OnEvent(Event& e)
	{
		//GP_CORE_INFO("{0}", e);
		EventDispatcher dispatcher(e);
	}
}