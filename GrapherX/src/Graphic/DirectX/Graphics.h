#pragma once
#include <wrl.h>
#include <tchar.h>
#include <d3d11.h>
#include <Windows.h>
#include "Graphic/ImGui/imgui_impl_dx11.h"
#include "Graphic/ImGui/imgui_impl_win32.h"

#include "Graphic/ImGui/ImguiManager.h"
namespace Grapher
{
	class Graphics
	{
	public:
		Graphics(HWND hwnd);
		Graphics(const Graphics& graphics) = delete;
		Graphics operator=(const Graphics& graphics)= delete;
		~Graphics();
		void EndFrame();
		void CreateRenderTarget();

	private:
		Microsoft::WRL::ComPtr < ID3D11Device> pDevice;
		Microsoft::WRL::ComPtr < IDXGISwapChain> pSwap;
		Microsoft::WRL::ComPtr < ID3D11DeviceContext> pContext;
		Microsoft::WRL::ComPtr < ID3D11RenderTargetView> g_mainRenderTargetView;

	private:

		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	};

}

