#include <myRenderer.h>
#include <memory>
#include "Scene3D.h"
#include "imgui.h"

namespace dx = DirectX;

Scene3D::Scene3D(dr::Win32Window& wnd)
	:
	wnd(wnd),
	light(wnd.Gfx()),
	Scene("Scene3D")
{
	wall.SetRootTransform(dx::XMMatrixTranslation(-1.5f, 0.0f, 0.0f));
	tp.SetPos({ 1.5f,0.0f,0.0f });
}

void Scene3D::Update(float dt)
{
	wnd.Gfx().SetCamera(cam3d.GetMatrix());
	light.Bind(wnd.Gfx(), cam3d.GetMatrix());

	cam3d.Camera3DController(wnd, dt);

}

void Scene3D::Draw(float dt)
{
	wall.Draw(wnd.Gfx());
	tp.Draw(wnd.Gfx());

	light.Draw(wnd.Gfx());

	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{
	// imgui window to control camera
	cam3d.SpawnControlWindow();
	light.SpawnControlWindow();

	wall.ShowWindow("Wall");
	tp.SpawnControlWindow(wnd.Gfx());
	//nano1.ShowWindow("Model 1");
}



