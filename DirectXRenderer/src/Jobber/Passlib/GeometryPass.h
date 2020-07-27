#pragma once
#include "Base/RenderQueuePass.h"
#include "Base/Source.h"
#include "Jobber/Job.h"
#include "Bindable/BindableCommon.h"
#include "Core/Camera/Camera3D.h"
#include <memory>

namespace dr
{
	class Graphics;

	namespace Rgph
	{
		class GeometryPass : public RenderQueuePass
		{
		public:
			GeometryPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				renderTargets = std::make_unique<ShaderInputMultiRenderTarget>(gfx, gfx.GetWidth(), gfx.GetHeight(),3);
				AddBind(VertexShader::Resolve(gfx, "Gbuffer_VS"));
				AddBind(PixelShader::Resolve(gfx, "GBuffer_PS"));
				AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));
				AddBind(Blender::Resolve(gfx, false));
				RegisterSource(DirectBindableSource<Bind::MultiRenderTarget>::Make("Gbuffer", renderTargets));
			}

			void Execute(Graphics& gfx)const noxnd override
			{
				renderTargets->Clear(gfx);
				pMainCamera->BindToGraphics(gfx);
				RenderQueuePass::Execute(gfx);
			}

			void BindMainCamera(const Camera3D& cam) noexcept
			{
				pMainCamera = &cam;
			}



		private:
			const Camera3D* pMainCamera = nullptr;

		};
	}
}