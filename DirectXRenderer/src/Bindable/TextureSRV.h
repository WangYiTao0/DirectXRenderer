#pragma once
#include "Bindable.h"
#include "Core/Surface.h"
namespace dr
{
	namespace Bind
	{
		class TextureSRV : public Bindable
		{
		public:
			TextureSRV(Graphics& gfx, ID3D11ShaderResourceView* pSRV, UINT slot = 0);
			void Bind(Graphics& gfx) noxnd override;
			static std::shared_ptr<TextureSRV> Resolve(Graphics& gfx, ID3D11ShaderResourceView* pSRV, UINT slot = 0);
			static std::string GenerateUID(ID3D11ShaderResourceView* pSRV, UINT slot = 0);
			std::string GetUID() const noexcept override;
		private:
			unsigned int slot;
		protected:
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTexture_SRV;
		};
	}
}
