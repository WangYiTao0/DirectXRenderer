#pragma once
#include "Jobber/Passlib/Base/RenderQueuePass.h"
#include "Bindable/BindableCommon.h"

#include "imgui.h"
namespace dr
{
	class Graphics;
	using namespace Bind;
	namespace Rgph
	{
		class RenderToTexturePass : public RenderQueuePass
		{
		public:
			RenderToTexturePass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{

				//RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));

				renderTarget = std::make_shared<ShaderInputRenderTarget>(gfx, gfx.GetWidth(), gfx.GetHeight(), 5);
		
				pSRV = renderTarget->GetSRV();

				RegisterSource(DirectBindableSource<Bind::RenderTarget>::Make("scratchOut", renderTarget));

				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
			}

			void Execute(Graphics& gfx) const noxnd override
			{
				renderTarget->Clear(gfx);
				RenderQueuePass::Execute(gfx);
			}

			void OnImGuiRender(Graphics& gfx)
			{
				ImGui::Begin("ViewPort");
				ImGui::Text("pointer = %p", pSRV);
				ImGui::Image(reinterpret_cast<void*>(pSRV), ImVec2((float)gfx.GetWidth(), (float)gfx.GetHeight()));
				ImGui::End();
			}
		private:
			ID3D11ShaderResourceView* pSRV;

		};

	}
}
