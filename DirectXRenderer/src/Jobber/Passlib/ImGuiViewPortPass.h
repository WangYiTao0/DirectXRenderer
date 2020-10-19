#pragma once
#include "Jobber/Passlib/Base/FullscreenPass.h"
#include "Bindable/BindableCommon.h"

#include "imgui.h"
namespace dr
{
	class Graphics;
	using namespace Bind;
	namespace Rgph
	{
		class ImGuiViewPortPass : public FullscreenPass
		{
		public:
			ImGuiViewPortPass(Graphics& gfx, std::string name)
				:
				FullscreenPass(std::move(name),gfx)
			{
				AddBindSink<Bind::RenderTarget>("scratchIn");
				//pSRV = renderTarget->GetSRV();
			}

			void Execute(Graphics& gfx) const noxnd override
			{

				FullscreenPass::Execute(gfx);
			}

			void OnImGuiRender(Graphics& gfx)
			{
				//ImGui::Begin("ViewPort");
				//ImGui::Text("pointer = %p", pSRV);
				//ImGui::Image(reinterpret_cast<void*>(pSRV), ImVec2((float)gfx.GetWidth(), (float)gfx.GetHeight()));
				//ImGui::End();
			}
		private:
			ID3D11ShaderResourceView* pSRV;
		};

	}
}
