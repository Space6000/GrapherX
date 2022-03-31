#pragma once
#include <memory>
#include <optional>
#include <Windows.h>
#include "Core/Log.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/GrapherXException.h"
#include "Graphic/DirectX/Graphics.h"
#include "Graphic/ImGui/imgui_impl_dx11.h"
#include "Graphic/ImGui/imgui_impl_win32.h"


namespace Grapher
{
	class WindowsWindow
	{
	public:
		// Exception Handeler for window
		class Exception : public GrapherXException
		{
		public:
			Exception(int line, const char* file, HRESULT Hresult);
			const char* what() const override;
			virtual const wchar_t* dis() const override;
			virtual const char* GetType() const override;
			static LPWSTR TranslateErrorCode(HRESULT Hresult) noexcept;
			HRESULT GetErrorCode() const;
			LPWSTR GetErrorString() const;

		private:
			HRESULT hr;
		};
	public:
		//Class Member Functions
		WindowsWindow(const LPCWSTR& WindowName, const unsigned int& width, const unsigned int& height);
		WindowsWindow(const WindowsWindow& window) = delete;
		WindowsWindow operator=(const WindowsWindow& window) = delete;
		~WindowsWindow();

		//Graphics
		Graphics& Gfx();

		//Process Windows Messages
		std::optional<int> ProcessMessage();

		//Set Events
		std::function<void(Event&)> EventCallback;
		inline virtual void SetEventCallback(const std::function<void(Event&)>& callback)  { EventCallback = callback; }
		
	private:
		//Window Message Handelar
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	private:

		//Width and Height of the window
		int window_width;
		int window_heigth;

		//Graphics Instance
		std::unique_ptr<Graphics> pGfx;
		
		//Window Instances
		HWND m_Hwnd;
		HMENU m_Menu;
		HINSTANCE m_HInst;

	};
}

