#include "drpch.h"
#include "ShaderToySampler.h"
#include "Debug/ThrowMacros.h"
#include "BindableCodex.h"

namespace dr
{
	namespace Bind
	{
		ShaderToySampler::ShaderToySampler(Graphics& gfx, Filter filter, Wrap wrap, int slot)
			:
			filter(filter),
			wrap(wrap),
			slot(slot)
		{
			INFOMAN(gfx);

			D3D11_SAMPLER_DESC samplerDesc = CD3D11_SAMPLER_DESC{ CD3D11_DEFAULT{} };

			switch (filter)
			{
			case Filter::Linear:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				break;
			case Filter::nearest:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				break;
			case Filter::Minimap:
				samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
				break;
			default:
				break;
			}

			switch (wrap)
			{
			case Wrap::Clamp:
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
				break;
			case Wrap::Repeat:
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				break;
			default:
				break;
			}

			samplerDesc.MaxAnisotropy = D3D11_REQ_MAXANISOTROPY;

			GFX_THROW_INFO(GetDevice(gfx)->CreateSamplerState(&samplerDesc, &pSampler));
		}

		void ShaderToySampler::Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(GetContext(gfx)->PSSetSamplers(slot, 1, pSampler.GetAddressOf()));
		}

		std::shared_ptr<dr::Bind::ShaderToySampler> ShaderToySampler::Resolve(Graphics& gfx, Filter filter, Wrap wrap, int slot)
		{
			return Codex::Resolve<ShaderToySampler>(gfx, filter, wrap, slot);
		}

		std::string ShaderToySampler::GenerateUID(Filter filter, Wrap wrap, int slot)
		{
			using namespace std::string_literals;
			return typeid(ShaderToySampler).name() + "#"s + std::to_string((int)filter) + std::to_string((int)wrap) + std::to_string(slot);
		}

		std::string ShaderToySampler::GetUID() const noexcept
		{
			return GenerateUID(filter, wrap, slot);
		}

	}
}
