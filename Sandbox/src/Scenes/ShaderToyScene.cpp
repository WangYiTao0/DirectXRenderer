#include "ShaderToyScene.h"
#include <myRenderer.h>

ShaderToyScene::ShaderToyScene(dr::Win32Window& wnd)
	:
	wnd(wnd),
	cam2d(wnd.Gfx(),"cam2D"),
	Scene("ShaderToyScene")
{
	cam2d.SetOrthoProjection((float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(), 0.0, 1.0);
	
	bufferA.SetPos({ (float)wnd.Gfx().GetWidth()/2.0f,(float)wnd.Gfx().GetHeight()/2.f,0.0 });
	bufferB.SetPos({ (float)wnd.Gfx().GetWidth() / 2.0f,(float)wnd.Gfx().GetHeight() / 2.f,0.0 });
	bufferC.SetPos({ (float)wnd.Gfx().GetWidth() / 2.0f,(float)wnd.Gfx().GetHeight() / 2.f,0.0 });
	Final.SetPos({ (float)wnd.Gfx().GetWidth() / 2.0f,(float)wnd.Gfx().GetHeight() / 2.f,0.0 });

	bufferA.LinkTechniques(rg);
	bufferB.LinkTechniques(rg);
	bufferC.LinkTechniques(rg);
	Final.LinkTechniques(rg);
}

void ShaderToyScene::Update(float dt)
{
	rg.BindCamera2D(cam2d);
}

void ShaderToyScene::Draw(float dt)
{
	bufferA.Submit(dr::Chan::Orth);
	bufferB.Submit(dr::Chan::Orth);
	bufferC.Submit(dr::Chan::Orth);
	Final.Submit(dr::Chan::Orth);
	rg.UpdatePSCB(wnd, dt);
	rg.Execute(wnd.Gfx());
}

void ShaderToyScene::Reset()
{
	rg.Reset();
}
