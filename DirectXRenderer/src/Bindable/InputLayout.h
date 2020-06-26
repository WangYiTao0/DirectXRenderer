#pragma once
#include "Bindable.h"
#include "Core/Vertex.h"

namespace dr
{
	namespace Bind
	{
	class InputLayout : public Bindable
	{
	public:
		InputLayout( Graphics& gfx,
			dr::Dvtx::VertexLayout layout,
			ID3DBlob* pVertexShaderBytecode );
		void Bind( Graphics& gfx ) noexcept override;
		static std::shared_ptr<Bindable> Resolve( Graphics& gfx,
			const dr::Dvtx::VertexLayout& layout,ID3DBlob* pVertexShaderBytecode );
		static std::string GenerateUID( const dr::Dvtx::VertexLayout& layout,ID3DBlob* pVertexShaderBytecode = nullptr );
		std::string GetUID() const noexcept override;
	protected:
		dr::Dvtx::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
	}
}