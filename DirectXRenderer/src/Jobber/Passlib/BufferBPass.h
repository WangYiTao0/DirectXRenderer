#pragma once
#include "Base/RenderQueuePass.h"
#include "Base/Source.h"
#include "../Job.h"
#include <vector>
#include "Bindable/BindableCommon.h"

namespace dr
{
	class Graphics;
	namespace Rgph
	{
		class BufferBPass : public RenderQueuePass
		{
		public:
			BufferBPass(Graphics& gfx, std::string name, unsigned int fullWidth,
				unsigned int fullHeight)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				renderTarget = std::make_unique<ShaderInputRenderTarget>(gfx,
					fullWidth / 2, fullHeight / 2, 4);
				AddBind(PixelShader::Resolve(gfx, "BufferB_PS"));

				AddBind(ShaderToySampler::Resolve(gfx,
					ShaderToySampler::Filter::Linear,
					ShaderToySampler::Wrap::Repeat, 0));
				RegisterSource(DirectBindableSource<Bind::RenderTarget>::Make("scratchOut", renderTarget));

				//AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				renderTarget->Clear(gfx);
				RenderQueuePass::Execute(gfx);
			}
		};
	}
}