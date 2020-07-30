#pragma once
#include "Base/RenderQueuePass.h"
#include "Jobber/Job.h"
#include <vector>
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/Stencil.h"
#include "Bindable/Blender.h"
#include "Core/Camera/Camera2D.h"
#include "Core/Win32Window.h"

namespace dr
{

	class Graphics;

	namespace Rgph
	{
		class Texture2DPass : public RenderQueuePass
		{
		public:
			Texture2DPass(Graphics& gfx, std::string name)
				:
				RenderQueuePass(std::move(name))
			{
				using namespace Bind;
				RegisterSink(DirectBufferSink<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSink(DirectBufferSink<DepthStencil>::Make("depthStencil", depthStencil));

				AddBind(PixelShader::Resolve(gfx, "Texture2D_PS"));
				AddBind(ShaderToySampler::Resolve(gfx,
					ShaderToySampler::Filter::Linear,
					ShaderToySampler::Wrap::Clamp, 1));
				AddBindSink<Bind::DepthStencil>("shadowMap");
				AddBindSink<Bind::RenderTarget>("bufferA");
				AddBindSink<Bind::RenderTarget>("bufferB");
				AddBindSink<Bind::RenderTarget>("bufferC");
				//AddBindSink<Bind::CachingPixelConstantBufferEx>("shaderToy");
				//RegisterSink(DirectBindableSink<CachingPixelConstantBufferEx>::Make("shaderToy", shaderToy));

				RegisterSource(DirectBufferSource<RenderTarget>::Make("renderTarget", renderTarget));
				RegisterSource(DirectBufferSource<DepthStencil>::Make("depthStencil", depthStencil));
				//AddBind(Stencil::Resolve(gfx, Stencil::Mode::Off));

				//depthStencil = std::make_unique<ShaderInputDepthStencil>(gfx, 0, DepthStencil::Usage::ShadowDepth);
				//RegisterSource(DirectBindableSource<DepthStencil>::Make("shadowOut", depthStencil));

			}
			void Bind2DCamera(const Camera2D& cam)
			{
				p2DCamera = &cam;
			}
			void Execute(Graphics& gfx) const noxnd override
			{
				depthStencil->Clear(gfx);
				p2DCamera->BindToGraphics(gfx);
				RenderQueuePass::Execute(gfx);
			}

			//void UpdatePixcelConstantBuffer(Win32Window& wnd, float dt)
			//{
			//	iTime += dt;

			//	auto buf = shaderToy->GetBuffer();
			//	buf["iResolution"] = DirectX::XMFLOAT3((float)wnd.Gfx().GetWidth(),(float)wnd.Gfx().GetHeight(),1.0);
			//	buf["iTime"] = iTime;
			//	buf["iMouse"] = DirectX::XMFLOAT4((float)wnd.mouse.GetPosX(),(float)wnd.mouse.GetPosY(),(int)wnd.mouse.LeftIsPressed(),
			//		(int)wnd.mouse.LeftIsPressed());

			//	shaderToy->SetBuffer(buf);
			//	shaderToy->Bind(wnd.Gfx());
			//}

			
		private:
			const Camera2D* p2DCamera = nullptr;
			float iTime = 0;
			std::shared_ptr<Bind::CachingPixelConstantBufferEx> shaderToy;
		};
	}
}