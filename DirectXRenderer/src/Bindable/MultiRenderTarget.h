#pragma once
#include "Bindable.h"
#include "BufferResource.h"

const UINT bufferCount = 4;

namespace dr
{
	class GraphicsResource;

	namespace Bind
	{
		class DepthStencil;

		class MultiRenderTarget : public Bindable, public BufferResource
		{
		public:
			void BindAsBuffer(Graphics& gfx) noxnd override;
			void BindAsBuffer(Graphics& gfx, BufferResource* depthStencil) noxnd override;
			void BindAsBuffer(Graphics& gfx, DepthStencil* depthStencil) noxnd;
			void Clear(Graphics& gfx) noxnd override;
			void Clear(Graphics& gfx, const std::array<float, 4>& color) noxnd;
			UINT GetWidth() const noexcept;
			UINT GetHeight() const noexcept;
		private:
			void BindAsBuffer(Graphics& gfx, ID3D11DepthStencilView* pDepthStencilView) noxnd;
		protected:
			MultiRenderTarget(Graphics& gfx, ID3D11Texture2D* pTexture[bufferCount]);
			MultiRenderTarget(Graphics& gfx, UINT width, UINT height);
			UINT width;
			UINT height;
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetView[bufferCount];
		};

		class ShaderInputMultiRenderTarget : public MultiRenderTarget
		{
		public:
			ShaderInputMultiRenderTarget(Graphics& gfx, UINT width, UINT height, UINT slot);
			void Bind(Graphics& gfx) noxnd override;
		private:
			UINT slot;
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pShaderResourceView[bufferCount];
		};

		// RT for Graphics to create RenderTarget for the back buffer
		class OutputOnlyMultiRenderTarget : public MultiRenderTarget
		{
			friend Graphics;
		public:
			void Bind(Graphics& gfx) noxnd override;
		private:
			OutputOnlyMultiRenderTarget(Graphics& gfx, ID3D11Texture2D* pTexture[bufferCount]);
		};
	}

}