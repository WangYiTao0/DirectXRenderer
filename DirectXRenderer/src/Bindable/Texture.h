#pragma once
#include "Bindable.h"
#include "Core/Surface.h"
namespace dr
{
	namespace Bind
	{
		class Texture : public Bindable
		{
		public:
			Texture(Graphics& gfx, const Surface& s);
			void Bind(Graphics& gfx) noexcept override;
		protected:
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pTextureView;
		};
	}
}
