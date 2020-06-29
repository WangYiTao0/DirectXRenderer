#pragma once
#include "Base/FullscreenPass.h"
#include "Bindable/ConstantBuffersEx.h"

namespace dr
{
	class Graphics;
	namespace Bind
	{
		class PixelShader;
		class RenderTarget;
	}

	namespace Rgph
	{
		class HorizontalBlurPass : public FullscreenPass
		{
		public:
			HorizontalBlurPass(std::string name, Graphics& gfx, unsigned int fullWidth, unsigned int fullHeight);
			void Execute(Graphics& gfx) const noxnd override;
		private:
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> direction;
		};
	}
}