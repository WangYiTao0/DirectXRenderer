#include "drpch.h"
#include "ShaderToyRenderGraph.h"
#include "Jobber/Passlib/BufferClearPass.h"
#include "Jobber/Passlib/Texture2DPass.h"
#include "Jobber/Passlib/ShadowMappingPass.h"

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
				auto pass = std::make_unique<ShadowMappingPass>(gfx, "shadowMap");
				AppendPass(std::move(pass));
			}

			/*
				float3 iResolution; // viewport resolution (in pixels)
				float iTime; // shader playback time (in seconds)
				float iTimeDelta; // render time (in seconds)
				int iFrame; // shader playback frame
				float iChannelTime[4]; // channel playback time (in seconds)
				float4 iMouse; // mouse pixel coords. xy: current (if MLB down), zw: click
				float4 iDate; // (year, month, day, time in seconds)
			*/
			//set up Comstant buffer
			{
				Dcb::RawLayout l;
				l.Add<Dcb::Float3>("iResolution");
				l.Add<Dcb::Float>("iTime");
				l.Add<Dcb::Float4>("iMouse");
				Dcb::Buffer buf{ std::move(l) };
				shaderToy = std::make_shared<Bind::CachingPixelConstantBufferEx>(gfx, buf, 0);
				AddGlobalSource(DirectBindableSource<Bind::CachingPixelConstantBufferEx>::Make("shaderToy", shaderToy));
			}


			{
				auto pass = std::make_unique<Texture2DPass>(gfx, "texture2D");
				pass->SetSinkLinkage("renderTarget", "clearRT.buffer");
				pass->SetSinkLinkage("depthStencil", "clearDS.buffer");
				pass->SetSinkLinkage("shadowMap", "shadowMap.map");
				pass->SetSinkLinkage("shaderToy", "$.shaderToy");
				AppendPass(std::move(pass));
			}

			SetSinkTarget("backbuffer", "texture2D.renderTarget");
			Finalize();
		}

		void ShaderToyRenderGraph::UpdatePSCB(Win32Window& wnd, float dt)
		{
			iTime += dt;

			auto buf = shaderToy->GetBuffer();
			buf["iTime"] = 1.0f;
			buf["iResolution"] = DirectX::XMFLOAT3{ (float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(), 1.0f };
			buf["iTime"] = iTime;
			buf["iMouse"] = DirectX::XMFLOAT4{ (float)wnd.mouse.GetPosX(), (float)wnd.mouse.GetPosY(), 
				(float)wnd.mouse.LeftIsPressed(),
				(float)wnd.mouse.LeftIsPressed() };

			shaderToy->SetBuffer(buf);
			shaderToy->Bind(wnd.Gfx());
		}

		void ShaderToyRenderGraph::BindCamera2D(Camera2D& cam)
		{
			dynamic_cast<Texture2DPass&>(FindPassByName("texture2D")).Bind2DCamera(cam);
		}


	}
}
