#pragma once

#include "../RenderGraph.h"

namespace dr
{
	class Graphics;
	namespace Rgph
	{
		class ShaderToyRenderGraph : public RenderGraph
		{
		public:
			ShaderToyRenderGraph(Graphics& gfx);
		};
	}
}