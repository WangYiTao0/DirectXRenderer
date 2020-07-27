#include "drpch.h"
#include "LightingPass.h"

namespace dr
{
	namespace Rgph
	{
		LightingPass::LightingPass(std::string name, Graphics& gfx, unsigned int fullWidth, unsigned int fullHeight)
			:
			FullscreenPass(std::move(name), gfx)
		{
			using namespace Bind;
			AddBind(PixelShader::Resolve(gfx, "DeferredLightingPass_PS"));
			AddBind(Blender::Resolve(gfx, false));
			AddBind(Sampler::Resolve(gfx, Sampler::Type::Point, true));

			RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));
			AddBindSink<Bind::MultiRenderTarget>("Gbuffer");
			RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
			RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
		}

		void LightingPass::Execute(Graphics& gfx) const noxnd
		{
			renderTargets->Clear(gfx);
			p2DCamera->BindToGraphics(gfx);
			FullscreenPass::Execute(gfx);
		}

		void LightingPass::Bind2DCamera(const Camera2D& cam)
		{
			p2DCamera = &cam;
		}
	}

}