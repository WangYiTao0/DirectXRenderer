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
				AddBindSink<Bind::DepthStencil>("shadowMap");
				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));

				//depthStencil = std::make_unique<ShaderInputDepthStencil>(gfx, 0, DepthStencil::Usage::ShadowDepth);
				//RegisterSource(DirectBindableSource<DepthStencil>::Make("shadowOut", depthStencil));

			}
			void Bind2DCamera(const Camera2D& cam)
			{
				p2DCamera = &cam;
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				depthStencil->Clear(gfx);
				p2DCamera->BindToGraphics(gfx);
				RenderQueuePass::Execute(gfx);
			}
		private:
			const Camera2D* p2DCamera = nullptr;
		};
	}
}