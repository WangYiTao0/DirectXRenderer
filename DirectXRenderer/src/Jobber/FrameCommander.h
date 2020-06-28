#pragma once
#include <array>
#include "Bindable/BindableCommon.h"
#include "CommonTool/StringHelper.h"
#include "Core/Graphics.h"
#include "Job.h"
#include "Pass.h"
#include "Debug/PerfLog.h"
#include "Core/DepthStencil.h"
#include "Core/RenderTarget.h"
#include <array>

namespace dr
{

	class FrameCommander
	{
	public:
		FrameCommander(Graphics& gfx)
			:
			ds(gfx, gfx.GetWidth(), gfx.GetHeight()),
			rt(gfx, gfx.GetWidth(), gfx.GetHeight())
		{
			namespace dx = DirectX;

			std::string shader_dir = StrH::GetShaderRootPath();

			// setup fullscreen geometry
			Dvtx::VertexLayout lay;
			lay.Append(Dvtx::VertexLayout::Position2D);
			Dvtx::VertexBuffer bufFull{ lay };
			bufFull.EmplaceBack(dx::XMFLOAT2{ -1,1 });
			bufFull.EmplaceBack(dx::XMFLOAT2{ 1,1 });
			bufFull.EmplaceBack(dx::XMFLOAT2{ -1,-1 });
			bufFull.EmplaceBack(dx::XMFLOAT2{ 1,-1 });
			pVbFull = Bind::VertexBuffer::Resolve(gfx, "$Full", std::move(bufFull));
			std::vector<unsigned short> indices = { 0,1,2,1,3,2 };
			pIbFull = Bind::IndexBuffer::Resolve(gfx, "$Full", std::move(indices));

			// setup fullscreen shaders
			pPsFull = Bind::PixelShader::Resolve(gfx, shader_dir+"Funk_PS.cso");
			pVsFull = Bind::VertexShader::Resolve(gfx, shader_dir+"Fullscreen_VS.cso");
			pLayoutFull = Bind::InputLayout::Resolve(gfx, lay, pVsFull->GetBytecode());
		}
		void Accept(Job job, size_t target) noexcept
		{
			passes[target].Accept(job);
		}
		void Execute(Graphics& gfx) const noxnd
		{
			using namespace Bind;
			// normally this would be a loop with each pass defining it setup / etc.
			// and later on it would be a complex graph with parallel execution contingent
			// on input / output requirements

			// setup render target used for normal passes
			ds.Clear(gfx);
			rt.BindAsTarget(gfx, ds);
			// main phong lighting pass
			Stencil::Resolve(gfx, Stencil::Mode::Off)->Bind(gfx);
			passes[0].Execute(gfx);
			// outline masking pass
			Stencil::Resolve(gfx, Stencil::Mode::Write)->Bind(gfx);
			NullPixelShader::Resolve(gfx)->Bind(gfx);
			passes[1].Execute(gfx);
			// outline drawing pass
			PerfLog::Start("Begin");
			Stencil::Resolve(gfx, Stencil::Mode::Mask)->Bind(gfx);
			struct SolidColorBuffer
			{
				DirectX::XMFLOAT4 color = { 1.0f,0.4f,0.4f,1.0f };
			} scb;
			PixelConstantBuffer<SolidColorBuffer>::Resolve(gfx, scb, 1u)->Bind(gfx);
			PerfLog::Mark("Resolve 2x");
			passes[2].Execute(gfx);
			// fullscreen funky pass
			gfx.BindSwapBuffer();
			rt.BindAsTexture(gfx, 0);
			pVbFull->Bind(gfx);
			pIbFull->Bind(gfx);
			pVsFull->Bind(gfx);
			pPsFull->Bind(gfx);
			pLayoutFull->Bind(gfx);
			gfx.DrawIndexed(pIbFull->GetCount());

		}
		void Reset() noexcept
		{
			for (auto& p : passes)
			{
				p.Reset();
			}
		}
	private:
		std::array<Pass, 3> passes;
		DepthStencil ds;
		RenderTarget rt;
		std::shared_ptr<Bind::VertexBuffer> pVbFull;
		std::shared_ptr<Bind::IndexBuffer> pIbFull;
		std::shared_ptr<Bind::VertexShader> pVsFull;
		std::shared_ptr<Bind::PixelShader> pPsFull;
		std::shared_ptr<Bind::InputLayout> pLayoutFull;
	};
}