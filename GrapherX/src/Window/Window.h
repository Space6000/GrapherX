#pragma once
#include "GrapherXwin.h"
#include "Core/GrapherXException.h"
#include "Core/Log.h"
#include "Graphic/DirectX/Graphics.h"
#include <optional>
#include <memory>
#include "Graphic/ImGui/imgui_impl_win32.h"

namespace Grapher
{
	class Window
	{
	public:
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
		Window(const LPCWSTR& WindowName, const unsigned int& width, const unsigned int& height);
		Window(const Window& window) = delete;
		Window operator=(const Window& window) = delete;
		~Window();

		Graphics& Gfx();

		static std::optional<int> ProcessMessage();

	private:

		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	private:

		std::unique_ptr<Graphics> pGfx;
		HWND m_Hwnd;
		HMENU m_Menu;
		HINSTANCE m_HInst;
	};

}

