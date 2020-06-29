#pragma once
#include "../RenderGraph.h"

namespace dr
{
	class Graphics;

	namespace Rgph
	{
		class ScaleOutlineRenderGraph : public RenderGraph
		{
		public:
			ScaleOutlineRenderGraph(Graphics& gfx);
		};
	}
}