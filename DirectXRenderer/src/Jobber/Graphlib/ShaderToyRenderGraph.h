#pragma once

#include "../RenderGraph.h"
#include "Bindable/ConstantBuffersEx.h"
#include "Debug/ConditionalNoexcept.h"
#include <memory>
#include "Core/Win32Window.h"

namespace dr
{
	class Graphics;
	class Camera2D;
	
	namespace Rgph
	{
		class ShaderToyRenderGraph : public RenderGraph
		{
		public:
			ShaderToyRenderGraph(Graphics& gfx);
			void RenderShaderToyWindow(Graphics& gfx, float dt);

			void UpdatePSCB(Win32Window& wnd, float dt);
			void BindCamera2D(Camera2D& cam);
		private:
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> shaderToy;
			float iTime = 0.0f;

		};
	}
}