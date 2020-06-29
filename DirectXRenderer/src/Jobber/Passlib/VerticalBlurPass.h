#pragma once
#include "Jobber/Passlib/Base/FullscreenPass.h"
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
		class VerticalBlurPass : public FullscreenPass
		{
		public:
			VerticalBlurPass(std::string name, Graphics& gfx);
			void Execute(Graphics& gfx) const noxnd override;
		private:
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> direction;
		};
	}
}