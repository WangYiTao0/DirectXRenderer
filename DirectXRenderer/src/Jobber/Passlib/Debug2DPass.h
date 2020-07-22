#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/Stencil.h"
#include "Bindable/Blender.h"
#include "Core/Camera/Camera2D.h"

namespace dr
{

	class Graphics;

	namespace Rgph
	{
		class Debug2DPass : public RenderQueuePass
		{
		public:
			Debug2DPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));
				AddBindSink<Bind::Bindable>("shadowMap");
				si_Ds = std::make_unique<ShaderInputDepthStencil>(gfx, 1, DepthStencil::Usage::ShadowDepth);
				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));

			}
			void Bind2DCamera(const Camera2D& cam)
			{
				p2DCamera = &cam;
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				si_Ds->Bind(gfx);
				p2DCamera->BindToGraphics(gfx);
				RenderQueuePass::Execute(gfx);
			}
		private:
			std::shared_ptr<dr::Bind::ShaderInputDepthStencil> si_Ds;
			const Camera2D* p2DCamera = nullptr;
		};
	}
}