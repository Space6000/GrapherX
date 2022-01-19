#include "Graphics.h"
#pragma comment(lib,"d3d11.lib")
#include "Graphic/ImGui/imgui_impl_dx11.h"
#include "Graphic/ImGui/imgui_impl_win32.h"

Grapher::Graphics::Graphics(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);
	ImGui_ImplDX11_Init(pDevice, pContext);
	CreateRenderTarget();
}

Grapher::Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
	if (pContext != nullptr)
	{
		pContext->Release();
	}
	if (pSwap != nullptr)
	{
		pSwap->Release();
	}
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}


	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

void Grapher::Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	static bool show_demo_window = true;
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	ImGui::Render();

	const float clear_color_with_alpha[4] = { 0,0,0,0 };
	pContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
	pContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


void Grapher::Graphics::CreateRenderTarget()
{
	ID3D11Texture2D* pBackBuffer;
	pSwap->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
	pBackBuffer->Release();
}

void Grapher::Graphics::CleanupRenderTarget()
{
	if (g_mainRenderTargetView) 
	{ 
		g_mainRenderTargetView->Release(); 
		g_mainRenderTargetView = NULL; 
	}

}
