#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/BindableCommon.h"
#include "Bindable/Stencil.h"
#include "Core/Camera/Camera3D.h"

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
				RenderQueuePass(std::move(name)),
				pShadowCBuf{ std::make_shared<Bind::ShadowCameraCBuf>(gfx) }
			{
				using namespace Bind;
				AddBind(pShadowCBuf);
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<dr::Bind::DepthStencil>::Make("depthStencil", depthStencil));
				AddBindSink<Bind::Bindable>("shadowMap");
				AddBind(std::make_shared<Bind::ShadowSampler>(gfx));
				AddBind(std::make_shared<Bind::Sampler>(gfx, Bind::Sampler::Type::Anisotropic, false, 2));
				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<dr::Bind::DepthStencil>::Make("depthStencil", depthStencil));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));
			}
			void BindMainCamera(const Camera3D& cam) noexcept
			{
				pMainCamera = &cam;
			}
			void BindShadowCamera(const Camera3D& cam) noexcept
			{
				pShadowCBuf->SetCamera(&cam);
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				assert(pMainCamera);
				pShadowCBuf->Update(gfx);
				pMainCamera->BindToGraphics(gfx);
				RenderQueuePass::Execute(gfx);
			}
		private:
			std::shared_ptr<Bind::ShadowCameraCBuf> pShadowCBuf;
			const Camera3D* pMainCamera = nullptr;
		};
	}
}