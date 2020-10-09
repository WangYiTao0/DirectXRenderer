#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Bindable/BindableCommon.h"

namespace dr
{
	class Graphics;

	namespace Rgph
	{
		class OutlineMaskGenerationPass : public RenderQueuePass
		{
		public:
			OutlineMaskGenerationPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				RegisterSink(DirectBufferSink<Bind::DepthStencil>::Make("depthStencil", depthStencil));
				RegisterSource(DirectBufferSource<Bind::DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(VertexShader::Resolve(gfx, "Solid_VS"));
				AddBind(NullPixelShader::Resolve(gfx));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Write));
				AddBind(Rasterizer::Resolve(gfx, false));
			}
		};
	}
}