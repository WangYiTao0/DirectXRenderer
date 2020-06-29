#include "drpch.h"
#include "PixelShader.h"
#include "Debug/ThrowMacros.h"
#include "BindableCodex.h"
#include "CommonTool/StringHelper.h"

namespace dr
{
	namespace Bind
	{
		PixelShader::PixelShader(Graphics& gfx, const std::string& path)
			:
			path(path)
		{
			INFOMAN(gfx);
			std::string shader_dir = "asset\\shader\\cso\\";
			Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
			GFX_THROW_INFO(D3DReadFileToBlob(dr::StrH::ToWide(shader_dir + path).c_str(), &pBlob));
			GFX_THROW_INFO(GetDevice(gfx)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));
		}

		void PixelShader::Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u));
		}
		std::shared_ptr<PixelShader> PixelShader::Resolve(Graphics& gfx, const std::string& path)
		{
			return Codex::Resolve<PixelShader>(gfx, path);
		}
		std::string PixelShader::GenerateUID(const std::string& path)
		{
			using namespace std::string_literals;
			return typeid(PixelShader).name() + "#"s + path;
		}
		std::string PixelShader::GetUID() const noexcept
		{
			return GenerateUID(path);
		}
	}
}