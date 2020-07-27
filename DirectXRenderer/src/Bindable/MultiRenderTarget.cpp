#include "drpch.h"
#include "MultiRenderTarget.h"
#include "Debug/ThrowMacros.h"
#include "DepthStencil.h"

namespace wrl = Microsoft::WRL;



namespace dr
{
	namespace Bind
	{

		MultiRenderTarget::MultiRenderTarget(Graphics& gfx, UINT width, UINT height)
			:
			width(width),
			height(height)
		{
			INFOMAN(gfx);

			// create texture resource
			D3D11_TEXTURE2D_DESC textureDesc = {};
			textureDesc.Width = width;
			textureDesc.Height = height;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE; // never do we not want to bind offscreen RTs as inputs
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;
			wrl::ComPtr<ID3D11Texture2D> pTexture[bufferCount];
			for (int i = 0; i < bufferCount; i++)
			{
				GFX_THROW_INFO(GetDevice(gfx)->CreateTexture2D(
					&textureDesc, nullptr, &pTexture[i]
				));
			}

			// create the target view on the texture
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
			rtvDesc.Format = textureDesc.Format;
			rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D = D3D11_TEX2D_RTV{ 0 };
			for (int i = 0; i < bufferCount; i++)
			{
				GFX_THROW_INFO(GetDevice(gfx)->CreateRenderTargetView(
					pTexture[i].Get(), &rtvDesc, &pTargetView[i]
				));
			}
		}

		MultiRenderTarget::MultiRenderTarget(Graphics& gfx, ID3D11Texture2D* pTexture[bufferCount])
		{
			INFOMAN(gfx);

			for (int i = 0; i < bufferCount; i++)
			{
				// get information from texture about dimensions
				D3D11_TEXTURE2D_DESC textureDesc;
				pTexture[i]->GetDesc(&textureDesc);
				width = textureDesc.Width;
				height = textureDesc.Height;

				// create the target view on the texture
				D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
				rtvDesc.Format = textureDesc.Format;
				rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				rtvDesc.Texture2D = D3D11_TEX2D_RTV{ 0 };
				GFX_THROW_INFO(GetDevice(gfx)->CreateRenderTargetView(
					pTexture[i], &rtvDesc, &pTargetView[i]
				));
			}
		}

		void MultiRenderTarget::BindAsBuffer(Graphics& gfx) noxnd
		{
			ID3D11DepthStencilView* const null = nullptr;
			BindAsBuffer(gfx, null);
		}

		void MultiRenderTarget::BindAsBuffer(Graphics& gfx, BufferResource* depthStencil) noxnd
		{
			assert(dynamic_cast<DepthStencil*>(depthStencil) != nullptr);
			BindAsBuffer(gfx, static_cast<DepthStencil*>(depthStencil));
		}

		void MultiRenderTarget::BindAsBuffer(Graphics& gfx, DepthStencil* depthStencil) noxnd
		{
			BindAsBuffer(gfx, depthStencil ? depthStencil->pDepthStencilView.Get() : nullptr);
		}

		void MultiRenderTarget::BindAsBuffer(Graphics& gfx, ID3D11DepthStencilView* pDepthStencilView) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(GetContext(gfx)->OMSetRenderTargets(bufferCount, pTargetView[0].GetAddressOf(), pDepthStencilView));

			// configure viewport
			D3D11_VIEWPORT vp;
			vp.Width = (float)width;
			vp.Height = (float)height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			vp.TopLeftX = 0.0f;
			vp.TopLeftY = 0.0f;
			GFX_THROW_INFO_ONLY(GetContext(gfx)->RSSetViewports(1u, &vp));
		}

		void MultiRenderTarget::Clear(Graphics& gfx, const std::array<float, 4>& color) noxnd
		{
			INFOMAN_NOHR(gfx);
			for (int i = 0; i < bufferCount; i++)
			{
				GFX_THROW_INFO_ONLY(GetContext(gfx)->ClearRenderTargetView(pTargetView[i].Get(), color.data()));
			}
		}

		void MultiRenderTarget::Clear(Graphics& gfx) noxnd
		{
			Clear(gfx, { 0.0f,0.0f,0.0f,0.0f });
		}

		UINT MultiRenderTarget::GetWidth() const noexcept
		{
			return width;
		}

		UINT MultiRenderTarget::GetHeight() const noexcept
		{
			return height;
		}
		ShaderInputMultiRenderTarget::ShaderInputMultiRenderTarget(Graphics& gfx, UINT width, UINT height, UINT slot)
			:
			MultiRenderTarget(gfx,width,height),
			slot(slot)
		{
			INFOMAN(gfx);

			for (int i = 0; i < bufferCount; i++)
			{
				wrl::ComPtr<ID3D11Resource> pRes;
				pTargetView[i]->GetResource(&pRes);

				// create the resource view on the texture
				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
				srvDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				srvDesc.Texture2D.MostDetailedMip = 0;
				srvDesc.Texture2D.MipLevels = 1;

				GFX_THROW_INFO(GetDevice(gfx)->CreateShaderResourceView(
					pRes.Get(), &srvDesc, &pShaderResourceView[i]
				));
			}


		}

		void ShaderInputMultiRenderTarget::Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			for (int i = 0; i < bufferCount; i++)
			{
				GFX_THROW_INFO_ONLY(GetContext(gfx)->PSSetShaderResources(i, 1, pShaderResourceView[i].GetAddressOf()));
			}
		}

		void OutputOnlyMultiRenderTarget::Bind(Graphics& gfx) noxnd
		{
			assert("Cannot bind OuputOnlyRenderTarget as shader input" && false);
		}

		OutputOnlyMultiRenderTarget::OutputOnlyMultiRenderTarget(Graphics& gfx, ID3D11Texture2D* pTexture[bufferCount])
			:
			MultiRenderTarget(gfx, pTexture)
		{}

	}
}

