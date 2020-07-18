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
		class BlurOutlineDrawingPass : public RenderQueuePass
		{
		public:
			BlurOutlineDrawingPass(Graphics& gfx, std::string name, unsigned int fullWidth, unsigned int fullHeight)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				renderTarget = std::make_unique<ShaderInputRenderTarget>(gfx, fullWidth / 2, fullHeight / 2, 0);
				AddBind(VertexShader::Resolve(gfx, "Solid_VS"));
				AddBind(PixelShader::Resolve(gfx, "Solid_PS"));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Mask));
				AddBind(Blender::Resolve(gfx, false));
				RegisterSource(DirectBindableSource<Bind::RenderTarget>::Make("scratchOut", renderTarget));
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				renderTarget->Clear(gfx);
				RenderQueuePass::Execute(gfx);
			}
		};
	}
}