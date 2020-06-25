#pragma once
#include "Win.h"
#include <d3d11.h>
#include <wrl.h>

namespace dr
{
	

	class Graphics
	{
	public:
		Graphics(HWND hWnd);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics();
		void EndFrame();
	private:
		Microsoft::WRL::ComPtr <ID3D11Device> m_pDevice;
		Microsoft::WRL::ComPtr <IDXGISwapChain> m_pSwapchain;
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_pContext;
		Microsoft::WRL::ComPtr <ID3D11RenderTargetView> m_pRenderTargetView;
	};
}