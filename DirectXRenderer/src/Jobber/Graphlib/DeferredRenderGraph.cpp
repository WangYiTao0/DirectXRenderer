#include "drpch.h"
#include "DeferredRenderGraph.h"
#include "Jobber/Passlib/BufferClearPass.h"
#include "Jobber/Passlib/GeometryPass.h"
#include "Jobber/Passlib/LightingPass.h"
#include "Jobber/Passlib/Texture2DPass.h"
#include <memory>

namespace dr
{
	namespace Rgph
	{
		DeferredRenderGraph::DeferredRenderGraph(Graphics& gfx)
			:
			RenderGraph(gfx)
		{
			{
				auto pass = std::make_unique<BufferClearPass>("clearRT");
				pass->SetSinkLinkage("buffer", "$.backbuffer");
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<BufferClearPass>("clearDS");
				pass->SetSinkLinkage("buffer", "$.masterDepth");
				AppendPass(std::move(pass));
			}

			{
				auto pass = std::make_unique<GeometryPass>(gfx,"GeometryPass");
				AppendPass(std::move(pass));
			}

			{
				auto pass = std::make_unique<Texture2DPass>(gfx, "texture2D");
				pass->SetSinkLinkage("Gbuffer", "GeometryPass.Gbuffer");
				pass->SetSinkLinkage("renderTarget", "clearRT.buffer");
				pass->SetSinkLinkage("depthStencil", "clearDS.buffer");
				AppendPass(std::move(pass));
			}

			{
				auto pass = std::make_unique<LightingPass>("LightingPass",gfx,gfx.GetWidth(),gfx.GetHeight());
				pass->SetSinkLinkage("Gbuffer", "GeometryPass.Gbuffer");
				pass->SetSinkLinkage("renderTarget", "texture2D.renderTarget");
				pass->SetSinkLinkage("depthStencil", "texture2D.depthStencil");
				AppendPass(std::move(pass));
			}
		}

		void DeferredRenderGraph::BindMainCamera(Camera3D& cam)
		{
			dynamic_cast<GeometryPass&>(FindPassByName("GeometryPass")).BindMainCamera(cam);
		}

		void DeferredRenderGraph::BindCamera2D(Camera2D& cam)
		{
			//dynamic_cast<GeometryPass&>(FindPassByName("GeometryPass")).Bind2DCamera(cam);
		}

	}
}
