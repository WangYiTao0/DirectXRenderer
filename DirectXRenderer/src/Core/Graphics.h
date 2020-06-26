#pragma once
#include "Win.h"
#include "Debug/DrException.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "Debug/DxgiInfoManager.h"
#include <DirectXMath.h>

namespace dr
{
	namespace Bind
	{
		class Bindable;
	}
	class Graphics
	{
		friend Bind::Bindable;
	public:
		class Exception : public DrException
		{
			using DrException::DrException;
		};
		class HrException : public Exception
		{
		public:
			HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			HRESULT GetErrorCode() const noexcept;
			std::string GetErrorString() const noexcept;
			std::string GetErrorDescription() const noexcept;
			std::string GetErrorInfo() const noexcept;

		private:
			HRESULT hr;
			std::string info;
		};
		class InfoException : public Exception
		{
		public:
			InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			std::string GetErrorInfo() const noexcept;
		private:
			std::string info;
		};
		class DeviceRemovedException : public HrException
		{
			using HrException::HrException;
		public:
			const char* GetType() const noexcept override;
		private:
			std::string reason;
		};
	public:
		Graphics(HWND hWnd, int width, int height);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics() = default;
		void EndFrame();
		void BeginFrame(float red, float green, float blue) noexcept;

		void DrawIndexed(UINT count) noxnd;
		void SetProjection(DirectX::FXMMATRIX proj)noexcept;
		DirectX::XMMATRIX GetProjection() const noexcept;

		void EnableImgui() noexcept;
		void DisableImgui() noexcept;
		bool IsImguiEnabled() const noexcept;
		
	private:
		bool imguiEnabled = true;
		DirectX::XMMATRIX m_projection;

		int screenWidth = 1600;
		int screenHeight = 900;

#ifndef NDEBUG
		DxgiInfoManager infoManager;
#endif
		Microsoft::WRL::ComPtr <ID3D11Device> m_pDevice;
		Microsoft::WRL::ComPtr <IDXGISwapChain> m_pSwapchain;
		Microsoft::WRL::ComPtr <ID3D11DeviceContext> m_pContext;
		Microsoft::WRL::ComPtr <ID3D11RenderTargetView> m_pRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDSV;
	};
}