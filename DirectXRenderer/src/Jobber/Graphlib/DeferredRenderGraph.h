#pragma once
#include "Jobber/RenderGraph.h"
#include "Debug/ConditionalNoexcept.h"

namespace dr
{
	class Graphics;
	class Camera3D;
	class Camera2D;

	namespace Bind
	{
		class Bindable;
		class RenderTarget;
	}

	namespace Rgph
	{
		class DeferredRenderGraph : public RenderGraph
		{
		public:
			DeferredRenderGraph(Graphics& gfx);
			void BindMainCamera(Camera3D& cam);
			void BindCamera2D(Camera2D& cam);
		};
	}
}
