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
				renderTarget = std::make_shared<ShaderInputRenderTarget>(gfx, gfx.GetWidth(), gfx.GetHeight(), 5);

				RegisterSource(DirectBindableSource<Bind::RenderTarget>::Make("scratchOut", renderTarget));
			}

			void Execute(Graphics& gfx) const noxnd override
			{
				renderTarget->Clear(gfx);
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
			ID3D11ShaderResourceView* pSRV;
			std::shared_ptr<RenderTarget> m_BackRTT;
		};

	}
}
