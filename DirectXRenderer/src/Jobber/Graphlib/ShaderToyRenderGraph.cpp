#include "drpch.h"
#include "ShaderToyRenderGraph.h"
#include "Jobber/Passlib/BufferClearPass.h"
#include "Jobber/Passlib/Texture2DPass.h"

namespace dr
{
	namespace Rgph
	{
		ShaderToyRenderGraph::ShaderToyRenderGraph(Graphics& gfx)
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
				auto pass = std::make_unique<Texture2DPass>(gfx, "texture2D");
				pass->SetSinkLinkage("renderTarget", "clearRT.buffer");
				pass->SetSinkLinkage("depthStencil", "clearDS.buffer");
				AppendPass(std::move(pass));
			}

			SetSinkTarget("backbuffer", "texture2D.renderTarget");
			Finalize();
		}
	}
}
