#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/Stencil.h"
#include "Bindable/Blender.h"

namespace dr
{

	class Graphics;

	namespace Rgph
	{
		class Texture2DPass : public RenderQueuePass
		{
		public:
			Texture2DPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));
				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));

			}			
			void Execute(Graphics& gfx) const noxnd override
			{
				RenderQueuePass::Execute(gfx);
			}
		};
	}
}