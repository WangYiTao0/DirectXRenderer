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
		class RTTPass : public RenderQueuePass
		{
		public:
			RTTPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));
				RegisterSink(DirectBufferSink<RenderTarget>::Make("backRTT", renderTarget));

				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
				RegisterSource(DirectBufferSource<RenderTarget>::Make("backRTT", renderTarget));
			}

			void Execute(Graphics& gfx) const noxnd override
			{
				//renderTargetTex->Clear(gfx);
				RenderQueuePass::Execute(gfx);
			}

			void OnImGuiRender(Graphics& gfx)
			{
				/*pSRV = renderTargetTex->GetSRV();
					ImGui::Begin("ViewPort");
					ImGui::Text("pointer = %p", pSRV);
					ImGui::Image(reinterpret_cast<void*>(pSRV), ImVec2((float)gfx.GetWidth(), (float)gfx.GetHeight()));
					ImGui::End();*/
			}
		private:
		/*	ID3D11ShaderResourceView* pSRV;
			std::shared_ptr<RenderTarget> m_BackRTT;*/
		};

	}
}
