#pragma once
#include "Window/GrapherXwin.h"
#include <d3d11.h>
#include <wrl.h>

#include <tchar.h>
namespace Grapher
{
	class Graphics
	{
	public:
		Graphics(HWND hwnd);
		Graphics(const Graphics& graphics) = delete;
		// Graphics& operater=(const Graphics ) = delete;
		~Graphics();
		void EndFrame();
		void CreateRenderTarget();
		void CleanupRenderTarget();

	//private:
		ID3D11Device* pDevice = nullptr;
		IDXGISwapChain* pSwap = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
		ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;


//mVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		//nst float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };

		//Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		//Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
		//Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;

	};

}

