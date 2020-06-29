#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/BindableCommon.h"
#include "Bindable/Stencil.h"

namespace dr
{

	class Graphics;

	namespace Rgph
	{
		class LambertianPass : public RenderQueuePass
		{
		public:
			LambertianPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<dr::Bind::DepthStencil>::Make("depthStencil", depthStencil));
				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<dr::Bind::DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));
			}
		};
	}
}