#include "drpch.h"
#include "Core/Graphics.h"
#include "Debug/dxerr.h"

#include "Debug/ThrowMacros.h"
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "DepthStencil.h"


namespace dr
{
	namespace wrl = Microsoft::WRL;

	Graphics::Graphics(HWND hWnd,int width, int height)
		:
		screenWidth(width),
		screenHeight(height)
	{
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = hWnd;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		UINT swapCreateFlags = 0u;
#ifndef NDEBUG
		swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// create device and front/back buffers, and swap chain and rendering context
		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,D3D_DRIVER_TYPE_HARDWARE,
			nullptr, swapCreateFlags,nullptr,0,
			D3D11_SDK_VERSION,
			&sd,
			m_pSwapchain.GetAddressOf(),
			m_pDevice.GetAddressOf(),
			nullptr,
			m_pContext.GetAddressOf()
		);

		GFX_THROW_INFO(hr);

		// gain access to texture subresource in swap chain (back buffer)
		wrl::ComPtr<ID3D11Resource> pBackBuffer;
		GFX_THROW_INFO(m_pSwapchain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
		GFX_THROW_INFO(m_pDevice->CreateRenderTargetView(pBackBuffer.Get(),nullptr,m_pRenderTargetView.GetAddressOf()));
	
	
		// create depth stensil state
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
		wrl::ComPtr<ID3D11DepthStencilState> pDSState;
		GFX_THROW_INFO(m_pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

		// bind depth state
		m_pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

		// configure viewport
		D3D11_VIEWPORT vp;
		vp.Width = (float)screenWidth;
		vp.Height = (float)screenHeight;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0.0f;
		vp.TopLeftY = 0.0f;
		m_pContext->RSSetViewports(1u, &vp);

		// init imgui d3d impl
		ImGui_ImplDX11_Init(m_pDevice.Get(), m_pContext.Get());
	}

	Graphics::~Graphics()
	{
		ImGui_ImplDX11_Shutdown();
	}

	void Graphics::EndFrame()
	{
		// imgui frame end
		if (imguiEnabled)
		{
			ImGuiIO& io = ImGui::GetIO();

			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}
		}

		HRESULT hr;
#ifndef NDEBUG
		infoManager.Set();
#endif
		if (FAILED(hr = m_pSwapchain->Present(1u, 0u)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				throw GFX_DEVICE_REMOVED_EXCEPT(m_pDevice->GetDeviceRemovedReason());
			}
			else
			{
				throw GFX_EXCEPT(hr);
			}
		}

	}

	void Graphics::BeginFrame(float red, float green, float blue) noexcept
	{
		// imgui begin frame
		if (imguiEnabled)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		}

		const float color[] = { red,green,blue,1.0f };
		m_pContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
		m_pContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
	}

	void Graphics::BindSwapBuffer() noexcept
	{
		m_pContext->OMSetRenderTargets(1u, m_pRenderTargetView.GetAddressOf(), nullptr);
	}

	void Graphics::BindSwapBuffer(const DepthStencil& ds) noexcept
	{
		m_pContext->OMSetRenderTargets(1u, m_pRenderTargetView.GetAddressOf(), ds.pDepthStencilView.Get());
	}

	void Graphics::DrawIndexed(UINT count) noxnd
	{
		GFX_THROW_INFO_ONLY(m_pContext->DrawIndexed(count, 0u, 0u));
	}

	void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
	{
		m_projection = proj;
	}

	DirectX::XMMATRIX Graphics::GetProjection() const noexcept
	{
		return m_projection;
	}

	void Graphics::SetCamera(DirectX::FXMMATRIX cam) noexcept
	{
		camera = cam;
	}

	DirectX::XMMATRIX Graphics::GetCamera() const noexcept
	{
		return camera;
	}
	void Graphics::EnableImgui() noexcept
	{
		imguiEnabled = true;
	}

	void Graphics::DisableImgui() noexcept
	{
		imguiEnabled = false;
	}

	bool Graphics::IsImguiEnabled() const noexcept
	{
		return imguiEnabled;
	}

	UINT Graphics::GetWidth() const noexcept
	{
		return screenWidth;
	}

	UINT Graphics::GetHeight() const noexcept
	{
		return screenHeight;
	}

	Graphics::HrException::HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs) noexcept
		:
		Exception(line, file),
		hr(hr)
	{
		// join all info messages with newlines into single string
		for (const auto& m : infoMsgs)
		{
			info += m;
			info.push_back('\n');
		}
		// remove final newline if exists
		if (!info.empty())
		{
			info.pop_back();
		}
	}

	const char* Graphics::HrException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
			<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
			<< "[Error String] " << GetErrorString() << std::endl
			<< "[Description] " << GetErrorDescription() << std::endl;
		if (!info.empty())
		{
			oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
		}
		oss << GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const char* Graphics::HrException::GetType() const noexcept
	{
		return "DR Graphics Exception";
	}

	HRESULT Graphics::HrException::GetErrorCode() const noexcept
	{
		return hr;
	}

	std::string Graphics::HrException::GetErrorString() const noexcept
	{
		return DXGetErrorString(hr);
	}

	std::string Graphics::HrException::GetErrorDescription() const noexcept
	{
		char buf[512];
		DXGetErrorDescription(hr, buf, sizeof(buf));
		return buf;
	}

	std::string Graphics::HrException::GetErrorInfo() const noexcept
	{
		return info;
	}

	const char* Graphics::DeviceRemovedException::GetType() const noexcept
	{
		return "DR Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
	}

	Graphics::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept
		:
		Exception(line, file)
	{
		// join all info messages with newlines into single string
		for (const auto& m : infoMsgs)
		{
			info += m;
			info.push_back('\n');
		}
		// remove final newline if exists
		if (!info.empty())
		{
			info.pop_back();
		}

	}

	const char* Graphics::InfoException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl
			<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
		oss << GetOriginString();
		whatBuffer = oss.str();
		return whatBuffer.c_str();
	}

	const char* Graphics::InfoException::GetType() const noexcept
	{
		return "DR Graphics Info Exception";
	}

	std::string Graphics::InfoException::GetErrorInfo() const noexcept
	{
		return info;
	}

}