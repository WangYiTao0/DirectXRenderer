#include <memory>
#include "Scene3D.h"
#include "imgui.h"
#include "TestModelProbe.h"

namespace dx = DirectX;

Scene3D::Scene3D(dr::Win32Window& wnd)
	:
	wnd(wnd),
	light(wnd.Gfx()),
	Scene("Scene3D")
{
	cube.SetPos({ 4.0f,0.0f,0.0f });
	cube2.SetPos({ 0.0f,4.0f,0.0f });

	cube.LinkTechniques(rg);
	cube2.LinkTechniques(rg);
	light.LinkTechniques(rg);
	sponza.LinkTechniques(rg);
}

void Scene3D::Update(float dt)
{
	wnd.Gfx().SetCamera(cam3d.GetMatrix());
	light.Bind(wnd.Gfx(), cam3d.GetMatrix());

	cam3d.Camera3DController(wnd, dt);

}

void Scene3D::Draw(float dt)
{
	light.Submit();
	cube.Submit();
	sponza.Submit();
	cube2.Submit();

	rg.Execute(wnd.Gfx());

	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{

	// Mesh techniques window

	static dr::MP modelProbe;
	modelProbe.SpawnWindow(sponza);

	// imgui window to control camera
	cam3d.SpawnControlWindow();
	light.SpawnControlWindow();
	modelProbe.SpawnWindow(sponza);
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");
	//fc.ShowWindows(wnd.Gfx());

	// present
	//wnd.Gfx().EndFrame();
	rg.Reset();
}



