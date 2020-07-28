#pragma once
#include "Bindable.h"
namespace dr
{
	namespace Bind
	{
		class ShaderToySampler : public Bindable
		{
		public:
			enum class Filter
			{
				Linear,
				nearest,
				Minimap,
			};
			enum class Wrap
			{
				Clamp,
				Repeat,
			};
		public:
			ShaderToySampler(Graphics& gfx, Filter filter, Wrap wrap, int slot);
			void Bind(Graphics& gfx) noxnd override;
			static std::shared_ptr<ShaderToySampler> Resolve(Graphics& gfx, Filter filter, Wrap wrap, int slot);
			static std::string GenerateUID(Filter filter, Wrap wrap, int slot);
			std::string GetUID() const noexcept override;
		protected:
			Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
			Filter filter;
			Wrap wrap;
			int slot;
		};
	}
}