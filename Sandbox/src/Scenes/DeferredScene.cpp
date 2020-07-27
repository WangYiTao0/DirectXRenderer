#include "DeferredScene.h"

DeferredScene::DeferredScene(dr::Win32Window& wnd)
	:wnd(wnd),
	light(wnd.Gfx(), { 10.0f,5.0f,0.0f }),
	Scene("Deferred Scene")
{
}

void DeferredScene::Update(float dt)
{

}

void DeferredScene::Draw(float dt)
{

}

void DeferredScene::Reset()
{

}
