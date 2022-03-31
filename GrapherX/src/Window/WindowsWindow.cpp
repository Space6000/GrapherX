#include "WindowsWindow.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Grapher
{
	// Class Exception
	WindowsWindow::Exception::Exception(int line, const char* file, HRESULT Hresult)
		:GrapherXException(line, file),
		hr(Hresult)
	{
	}

	const char* WindowsWindow::Exception::what() const
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "\t[Error Code] " << GetErrorCode() << std::endl
			<< GetOriginString();
		whatBuffer = oss.str();
	
		return whatBuffer.c_str();
	}

	const wchar_t* WindowsWindow::Exception::dis() const
	{
		return GetErrorString();
	}

	const char* WindowsWindow::Exception::GetType() const
	{
		return "Window Class Error";
	}

	LPWSTR WindowsWindow::Exception::TranslateErrorCode(HRESULT Hresult) noexcept
	{
		LPWSTR pBuffer = nullptr;
		// windows will allocate memory for err string and make our pointer point to it
		DWORD nMsgLen = FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, Hresult, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&pBuffer, 0, nullptr
		);
		// 0 string length returned indicates a failure
		if (nMsgLen == 0)
		{
			return L"Unidentified error code";
		}
		return pBuffer;
	}

	HRESULT WindowsWindow::Exception::GetErrorCode() const
	{
		return hr;
	}

	LPWSTR WindowsWindow::Exception::GetErrorString() const
	{
		return TranslateErrorCode(hr);
	}

	// Class Window
	WindowsWindow::WindowsWindow(const LPCWSTR& WindowName, const unsigned int& width, const unsigned int& height)
		: window_width(width), window_heigth(height)
	{

		WNDCLASSEX wc = { 0 };

		wc.cbClsExtra = NULL;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.cbWndExtra = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hInstance = m_HInst;
		wc.lpszClassName = L"MyWindowClass";
		wc.lpszMenuName = L"";
		wc.style = NULL;
		wc.lpfnWndProc = HandleMsgSetup;
		wc.hbrBackground = nullptr;

		RegisterClassEx(&wc);

		// Creating Window
		m_Hwnd = ::CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,
			L"MyWindowClass",
			WindowName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			NULL, NULL, NULL, NULL
		);


		// Display the window
		ShowWindow(m_Hwnd, SW_SHOW);

		pGfx = std::make_unique<Graphics>(m_Hwnd);
	}

	WindowsWindow::~WindowsWindow()
	{
		ImGui_ImplWin32_Shutdown();
		UnregisterClassA("MyWindowClass", m_HInst);
		DestroyWindow(m_Hwnd);
	}

	Graphics& WindowsWindow::Gfx()
	{
		return *pGfx;
	}

	std::optional<int> WindowsWindow::ProcessMessage()
	{
		MSG msg;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{

			if (msg.message == WM_QUIT)
			{
				return msg.wParam;
			}

			switch (msg.message)
			{
				/*********** KEYBOARD MESSAGES ***********/

				// syskey commands need to be handled to track ALT key (VK_MENU) and F10
			case WM_SYSKEYDOWN:
			{
				KeyPressedEvent keyPressedEvent(static_cast<unsigned char>(msg.wParam), static_cast<unsigned char>(msg.lParam));
				EventCallback(keyPressedEvent);				
				break;
			}
			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				KeyReleasedEvent keyReleasedEvent(static_cast<unsigned char>(msg.wParam));
				EventCallback(keyReleasedEvent);
				break;
			}
			case WM_CHAR:
				//kbd.OnChar(static_cast<unsigned char>(wParam));
				break;
				/*********** END KEYBOARD MESSAGES ***********/

				/************* MOUSE MESSAGES ****************/
			case WM_MOUSEMOVE:
			{
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseMovedEvent mouseMovedEvent(pt.x, pt.y);
				EventCallback(mouseMovedEvent);
				break;
			}
			case WM_LBUTTONDOWN:
			{
				
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseLeftPressedEvent mouseLeftPressedEvent(pt.x, pt.y);
				EventCallback(mouseLeftPressedEvent);
				break;
			}
			case WM_RBUTTONDOWN:
			{
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseRightPressedEvent mouseRightPressedEvent(pt.x, pt.y);
				EventCallback(mouseRightPressedEvent);
				break;
			}
			case WM_LBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseLeftReleasedEvent mouseLeftReleasedEvent(pt.x, pt.y);
				EventCallback(mouseLeftReleasedEvent);
				break;
			}
			case WM_RBUTTONUP:
			{
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseRightReleasedEvent mouseRightReleasedEvent(pt.x, pt.y);
				EventCallback(mouseRightReleasedEvent);
				break;
			}
			case WM_MOUSEWHEEL:
			{
				const POINTS pt = MAKEPOINTS(msg.lParam);
				MouseScrolledEvent mouseScrolledEvent(pt.x, pt.y);
				EventCallback(mouseScrolledEvent);
				break;
			}
			/************** END MOUSE MESSAGES **************/
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return {};
	}


	LRESULT WINAPI WindowsWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowsWindow* const pWnd = static_cast<WindowsWindow*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::HandleMsgThunk));
			// forward message to window class handler
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if we get a message before the WM_NCCREATE message, handle with default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI WindowsWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// retrieve ptr to window class
		WindowsWindow* const pWnd = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window class handler
 		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}


	LRESULT WindowsWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{

		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		switch (msg)
		{
			case WM_DESTROY:
				::PostQuitMessage(0);
				return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}