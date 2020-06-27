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
	bluePlane.SetPos(cam3d.GetPos());
	redPlane.SetPos(cam3d.GetPos());
}

void Scene3D::Update(float dt)
{
	wnd.Gfx().SetCamera(cam3d.GetMatrix());
	light.Bind(wnd.Gfx(), cam3d.GetMatrix());

	cam3d.Camera3DController(wnd, dt);

}

void Scene3D::Draw(float dt)
{
	light.Draw(wnd.Gfx());

	sponza.Draw(wnd.Gfx());
	bluePlane.Draw(wnd.Gfx());
	redPlane.Draw(wnd.Gfx());
	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{
	// imgui window to control camera
	cam3d.SpawnControlWindow();
	light.SpawnControlWindow();

	sponza.ShowWindow(wnd.Gfx(), "Sponza");
	bluePlane.SpawnControlWindow(wnd.Gfx(), "Blue Plane");
	redPlane.SpawnControlWindow(wnd.Gfx(), "Red Plane");
}



