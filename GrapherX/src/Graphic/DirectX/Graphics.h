#pragma once
#include "Window/GrapherXwin.h"
#include <d3d11.h>
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
	private:
		ID3D11Device* pDevice = nullptr;
		IDXGISwapChain* pSwap = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
	};

}

