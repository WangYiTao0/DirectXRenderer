#include "drpch.h"
#include "BlurOutlineRenderGraph.h"
#include "Jobber/Passlib/BufferClearPass.h"
#include "Jobber/Passlib/LambertianPass.h"
#include "Jobber/Passlib/OutlineDrawingPass.h"
#include "Jobber/Passlib/OutlineMaskGenerationPass.h"
#include "Jobber/Passlib/Base/Source.h"
#include "Jobber/Passlib/HorizontalBlurPass.h"
#include "Jobber/Passlib/VerticalBlurPass.h"
#include "Jobber/Passlib/BlurOutlineDrawingPass.h"
#include "Jobber/Passlib/WireframePass.h"
#include "Jobber/Passlib/ShadowMappingPass.h"
#include "Bindable/BindableCommon.h"
#include "CommonTool/DrMath.h"
#include <imgui/imgui.h>
#include "Jobber/Passlib/SkyboxPass.h"

#include "Jobber/Passlib/RenderToTexturePass.h"
#include "Jobber/Passlib/ImGuiViewPortPass.h"
namespace dr
{
	namespace Rgph
	{
		BlurOutlineRenderGraph::BlurOutlineRenderGraph(Graphics& gfx)
			:
			//backbufferTexture(std::make_shared<ShaderInputRenderTarget>(gfx, gfx.GetWidth(), gfx.GetHeight(), 5)),

			RenderGraph(gfx)
		{
			//AddGlobalSource(DirectBufferSource<Bind::RenderTarget>::Make("backbufferRT", backbufferTexture));
			//AddGlobalSink(DirectBufferSink<Bind::RenderTarget>::Make("backbufferRT", backbufferTexture));
			//AddGlobalSource(DirectBindableSource<Bind::RenderTarget>::Make("backbufferRT_scratchOut", backbufferTexture));

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

	/*		{
				auto pass = std::make_unique<BufferClearPass>("clearBRT");
				pass->SetSinkLinkage("buffer", "$.backbufferRT");
				AppendPass(std::move(pass));
			}*/


			{
				auto pass = std::make_unique<RenderToTexturePass>(gfx, "backRenderToTexture");
				pass->SetSinkLinkage("depthStencil", "clearDS.buffer");
				//pass->SetSinkLinkage("renderTarget", "clearRT.buffer");
				AppendPass(std::move(pass));
			}
	

			{
				auto pass = std::make_unique<ShadowMappingPass>(gfx, "shadowMap");
				AppendPass(std::move(pass));
			}


			{
				auto pass = std::make_unique<LambertianPass>(gfx, "lambertian");
				pass->SetSinkLinkage("shadowMap", "shadowMap.map");
				pass->SetSinkLinkage("depthStencil", "backRenderToTexture.depthStencil");
				pass->SetSinkLinkage("renderTarget", "backRenderToTexture.renderTarget");
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<SkyboxPass>(gfx, "skybox");
				pass->SetSinkLinkage("renderTarget", "lambertian.renderTarget");
				pass->SetSinkLinkage("depthStencil", "lambertian.depthStencil");
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<OutlineMaskGenerationPass>(gfx, "outlineMask");
				pass->SetSinkLinkage("depthStencil", "skybox.depthStencil");
				AppendPass(std::move(pass));
			}

			// setup blur constant buffers
			{
				{
					Dcb::RawLayout l;
					l.Add<Dcb::Integer>("nTaps");
					l.Add<Dcb::Array>("coefficients");
					l["coefficients"].Set<Dcb::Float>(maxRadius * 2 + 1);
					Dcb::Buffer buf{ std::move(l) };
					blurKernel = std::make_shared<Bind::CachingPixelConstantBufferEx>(gfx, buf, 0);
					SetKernelGauss(radius, sigma);
					AddGlobalSource(DirectBindableSource<Bind::CachingPixelConstantBufferEx>::Make("blurKernel", blurKernel));
				}
				{
					Dcb::RawLayout l;
					l.Add<Dcb::Bool>("isHorizontal");
					Dcb::Buffer buf{ std::move(l) };
					blurDirection = std::make_shared<Bind::CachingPixelConstantBufferEx>(gfx, buf, 1);
					AddGlobalSource(DirectBindableSource<Bind::CachingPixelConstantBufferEx>::Make("blurDirection", blurDirection));
				}
			}

			{
				auto pass = std::make_unique<BlurOutlineDrawingPass>(gfx, "outlineDraw", gfx.GetWidth(), gfx.GetHeight());
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<HorizontalBlurPass>("horizontal", gfx, gfx.GetWidth(), gfx.GetHeight());
				pass->SetSinkLinkage("scratchIn", "outlineDraw.scratchOut");
				pass->SetSinkLinkage("kernel", "$.blurKernel");
				pass->SetSinkLinkage("direction", "$.blurDirection");
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<VerticalBlurPass>("vertical", gfx);
				pass->SetSinkLinkage("renderTarget", "skybox.renderTarget");
				pass->SetSinkLinkage("depthStencil", "outlineMask.depthStencil");
				pass->SetSinkLinkage("scratchIn", "horizontal.scratchOut");
				pass->SetSinkLinkage("kernel", "$.blurKernel");
				pass->SetSinkLinkage("direction", "$.blurDirection");
				AppendPass(std::move(pass));
			}
			{
				auto pass = std::make_unique<WireframePass>(gfx, "wireframe");
				pass->SetSinkLinkage("renderTarget", "vertical.renderTarget");
				pass->SetSinkLinkage("depthStencil", "vertical.depthStencil");
				AppendPass(std::move(pass));
			}

			{
				auto pass = std::make_unique<ImGuiViewPortPass>(gfx, "ImGuiViewPort");
				pass->SetSinkLinkage("renderTarget", "clearRT.buffer");
				pass->SetSinkLinkage("depthStencil", "wireframe.depthStencil");
				pass->SetSinkLinkage("scratchIn", "backRenderToTexture.scratchOut");
				AppendPass(std::move(pass));
			}

			SetSinkTarget("backbuffer", "ImGuiViewPort.renderTarget");

			//SetSinkTarget("backbuffer", "$.backbufferRT");



			Finalize();
		}


		void BlurOutlineRenderGraph::SetKernelGauss(int radius, float sigma) noxnd
		{
			assert(radius <= maxRadius);
			auto k = blurKernel->GetBuffer();
			const int nTaps = radius * 2 + 1;
			k["nTaps"] = nTaps;
			float sum = 0.0f;
			for (int i = 0; i < nTaps; i++)
			{
				const auto x = float(i - radius);
				const auto g = gauss(x, sigma);
				sum += g;
				k["coefficients"][i] = g;
			}
			for (int i = 0; i < nTaps; i++)
			{
				k["coefficients"][i] = (float)k["coefficients"][i] / sum;
			}
			blurKernel->SetBuffer(k);
		}

		void BlurOutlineRenderGraph::SetKernelBox(int radius) noxnd
		{
			assert(radius <= maxRadius);
			auto k = blurKernel->GetBuffer();
			const int nTaps = radius * 2 + 1;
			k["nTaps"] = nTaps;
			const float c = 1.0f / nTaps;
			for (int i = 0; i < nTaps; i++)
			{
				k["coefficients"][i] = c;
			}
			blurKernel->SetBuffer(k);
		}

		void BlurOutlineRenderGraph::OnImGuiRender(Graphics& gfx)
		{
			RenderShadowWindow(gfx);
			RenderKernelWindow(gfx);
			RenderViewPort(gfx);
		}


		void BlurOutlineRenderGraph::RenderKernelWindow(Graphics& gfx)
		{
			if (ImGui::Begin("Kernel"))
			{
				bool filterChanged = false;
				{
					const char* items[] = { "Gauss","Box" };
					static const char* curItem = items[0];
					if (ImGui::BeginCombo("Filter Type", curItem))
					{
						for (int n = 0; n < std::size(items); n++)
						{
							const bool isSelected = (curItem == items[n]);
							if (ImGui::Selectable(items[n], isSelected))
							{
								filterChanged = true;
								curItem = items[n];
								if (curItem == items[0])
								{
									kernelType = KernelType::Gauss;
								}
								else if (curItem == items[1])
								{
									kernelType = KernelType::Box;
								}
							}
							if (isSelected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}
						ImGui::EndCombo();
					}
				}

				bool radChange = ImGui::SliderInt("Radius", &radius, 0, maxRadius);
				bool sigChange = ImGui::SliderFloat("Sigma", &sigma, 0.1f, 10.0f);
				if (radChange || sigChange || filterChanged)
				{
					if (kernelType == KernelType::Gauss)
					{
						SetKernelGauss(radius, sigma);
					}
					else if (kernelType == KernelType::Box)
					{
						SetKernelBox(radius);
					}
				}
			}
			ImGui::End();
		}

		void BlurOutlineRenderGraph::RenderViewPort(Graphics& gfx)
		{
			dynamic_cast<RenderToTexturePass&>(FindPassByName("backRenderToTexture")).OnImGuiRender(gfx);
		}

		void Rgph::BlurOutlineRenderGraph::RenderShadowWindow(Graphics& gfx)
		{
			if (ImGui::Begin("Shadow"))
			{
				if (ImGui::Button("Dump Cubemap"))
				{
					DumpShadowMap(gfx, "Dumps\\shadow_");
				}
			}
			ImGui::End();
		}

		void Rgph::BlurOutlineRenderGraph::BindMainCamera(Camera3D& cam)
		{
			dynamic_cast<LambertianPass&>(FindPassByName("lambertian")).BindMainCamera(cam);
			dynamic_cast<SkyboxPass&>(FindPassByName("skybox")).BindMainCamera(cam);
		}
		void Rgph::BlurOutlineRenderGraph::BindShadowCamera(Camera3D& cam)
		{
			dynamic_cast<ShadowMappingPass&>(FindPassByName("shadowMap")).BindShadowCamera(cam);
			dynamic_cast<LambertianPass&>(FindPassByName("lambertian")).BindShadowCamera(cam);
		}
		void Rgph::BlurOutlineRenderGraph::DumpShadowMap(Graphics& gfx, const std::string& path)
		{
			dynamic_cast<ShadowMappingPass&>(FindPassByName("shadowMap")).DumpShadowMap(gfx, path);
		}
	}
}
