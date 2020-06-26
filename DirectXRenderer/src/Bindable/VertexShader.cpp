#include "drpch.h"
#include "VertexShader.h"
#include "Debug/ThrowMacros.h"
#include "BindableCodex.h"
#include <typeinfo>

namespace dr
{
	namespace Bind
	{
		VertexShader::VertexShader(Graphics& gfx, const std::string& path)
		{
			INFOMAN(gfx);

			GFX_THROW_INFO(D3DReadFileToBlob(std::wstring{ path.begin(),path.end() }.c_str(), &pBytecodeBlob));
			GFX_THROW_INFO(GetDevice(gfx)->CreateVertexShader(
				pBytecodeBlob->GetBufferPointer(),
				pBytecodeBlob->GetBufferSize(),
				nullptr,
				&pVertexShader));
		}

		void VertexShader::Bind(Graphics& gfx) noexcept
		{
			GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
		}

		ID3DBlob* VertexShader::GetBytecode() const noexcept
		{
			return pBytecodeBlob.Get();
		}

		std::shared_ptr<VertexShader> VertexShader::Resolve(Graphics& gfx, const std::string& path)
		{
			return Codex::Resolve<VertexShader>(gfx, path);
		}
		std::string VertexShader::GenerateUID(const std::string& path)
		{
			using namespace std::string_literals;
			return typeid(VertexShader).name() + "#"s + path;
		}
		std::string VertexShader::GetUID() const noexcept
		{
			return GenerateUID(path);
		}

	}
}


