#include "drpch.h"
#include "TextureSRV.h"
#include "Debug/ThrowMacros.h"
#include "BindableCodex.h"

namespace dr
{
	namespace Bind
	{
		TextureSRV::TextureSRV(Graphics& gfx, ID3D11ShaderResourceView* pSRV, UINT slot)
			:
			pTexture_SRV(pSRV),
			slot(slot)
		{
		}

		void TextureSRV:: Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(GetContext(gfx)->PSSetShaderResources(slot, 1u, pTexture_SRV.GetAddressOf()));
		}

		std::shared_ptr<dr::Bind::TextureSRV> TextureSRV::Resolve(Graphics& gfx, ID3D11ShaderResourceView* pSRV, UINT slot /*= 0*/)
		{
			return Codex::Resolve<TextureSRV>(gfx, pSRV, slot);
		}

		std::string TextureSRV::GenerateUID(ID3D11ShaderResourceView* pSRV, UINT slot /*= 0*/)
		{
			using namespace std::string_literals;
			return typeid(TextureSRV).name() + "#"s + "#" + std::to_string(slot);
		}

		std::string TextureSRV::GetUID() const noexcept
		{
			return std::string();
		}

	}
}