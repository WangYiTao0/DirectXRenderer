#include "ShaderToyScene.h"
#include <myRenderer.h>

ShaderToyScene::ShaderToyScene(dr::Win32Window& wnd)
	:
	wnd(wnd),
	cam2d(wnd.Gfx(),"cam2D"),
	Scene("ShaderToyScene")
{
	cam2d.SetOrthoProjection((float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(), 0.0, 1.0);
	
	t2d.SetPos({ 100,100,0 });
	
	t2d.LinkTechniques(rg);
}

void ShaderToyScene::Update(float dt)
{
	cam2d.BindToGraphics(wnd.Gfx());
}

void ShaderToyScene::Draw(float dt)
{
	t2d.Submit(dr::Chan::Orth);
	rg.Execute(wnd.Gfx());
}

void ShaderToyScene::Reset()
{
	rg.Reset();
}
