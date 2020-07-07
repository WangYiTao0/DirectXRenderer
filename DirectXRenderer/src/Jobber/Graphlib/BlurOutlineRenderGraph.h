#pragma once
#include "Jobber/RenderGraph.h"
#include <memory>
#include "Debug/ConditionalNoexcept.h"
#include "Bindable/ConstantBuffersEx.h"

namespace dr
{
	class Graphics;
	class Camera3D;

	namespace Bind
	{
		class Bindable;
		class RenderTarget;
		class ShadowSampler;
		class ShadowRasterizer;
	}

	namespace Rgph
	{
		class BlurOutlineRenderGraph : public RenderGraph
		{
		public:
			BlurOutlineRenderGraph(Graphics& gfx);
			void RenderWindows(Graphics& gfx);
			void BindMainCamera(Camera3D& cam);
			void BindShadowCamera(Camera3D& cam);
			void DumpShadowMap(Graphics& gfx, const std::string& path);
		private:
			void RenderKernelWindow(Graphics& gfx);
			void RenderShadowWindow(Graphics& gfx);
			// private functions
			void SetKernelGauss(int radius, float sigma) noxnd;
			void SetKernelBox(int radius)noxnd;
			// private data
			enum class KernelType
			{
				Gauss,
				Box,
			} kernelType = KernelType::Gauss;
			static constexpr int maxRadius = 7;
			int radius = 4;
			float sigma = 2.0f;
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> blurKernel;
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> blurDirection;
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> shadowControl;
			std::shared_ptr<Bind::ShadowSampler> shadowSampler;
			std::shared_ptr<Bind::ShadowRasterizer> shadowRasterizer;
		};
	}
}