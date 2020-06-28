#pragma once
#include "Graphics.h"
#include "GraphicsResource.h"

namespace dr
{
	class DepthStencil;

	class RenderTarget : public GraphicsResource
	{
	public:
		RenderTarget(Graphics& gfx, UINT width, UINT height);
		void BindAsTexture(Graphics& gfx, UINT slot) const noexcept;
		void BindAsTarget(Graphics& gfx) const noexcept;
		void BindAsTarget(Graphics& gfx, const DepthStencil& depthStencil) const noexcept;
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;//ID3D11ShaderResourceView
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTargetView;
	};
}