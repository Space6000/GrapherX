#include "Window.h"

namespace Grapher
{
	// Class Exception
	Window::Exception::Exception(int line, const char* file, HRESULT Hresult)
		:GrapherXException(line, file),
		hr(Hresult)
	{
	}

	const char* Window::Exception::what() const
	{

		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "\t[Error Code] " << GetErrorCode() << std::endl
			<< GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const wchar_t* Window::Exception::dis() const
	{
		return GetErrorString();
	}

	const char* Window::Exception::GetType() const
	{
		return "Window Class Error";
	}

	LPWSTR Window::Exception::TranslateErrorCode(HRESULT Hresult) noexcept
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
		//wprintf(pBuffer);
		return pBuffer;
	}

	HRESULT Window::Exception::GetErrorCode() const
	{
		return hr;
	}

	LPWSTR Window::Exception::GetErrorString() const
	{
		return TranslateErrorCode(hr);
	}

	// Class Window
	Window::Window(const LPCWSTR& WindowName, const unsigned int& width, const unsigned int& height)
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

		// Showing the window
		ShowWindow(m_Hwnd, SW_SHOW);

		pGfx = std::make_unique<Graphics>(m_Hwnd);
	}

	Window::~Window()
	{
		DestroyWindow(m_Hwnd);
	}

	Graphics& Window::Gfx()
	{
		return *pGfx;
	}

	std::optional<int> Window::ProcessMessage()
	{
		MSG msg;

		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return {};
	}

	// Private function of class window..
	

	LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
			// forward message to window class handler
			return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
		}
		// if we get a message before the WM_NCCREATE message, handle with default handler
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// retrieve ptr to window class
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_KEYDOWN:
		{
			
			break;
		}
		case WM_KEYUP:
		{
			break;
		}
		case WM_CHAR:
		{
			break;
		}
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}