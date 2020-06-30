#include <myRenderer.h>
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
	cameras.AddCamera(std::make_unique<dr::Camera3D>(wnd.Gfx(), "A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, dr::PI / 2.0f));
	cameras.AddCamera(std::make_unique<dr::Camera3D>(wnd.Gfx(), "B", dx::XMFLOAT3{ -13.5f,28.8f,-6.4f }, dr::PI / 180.0f * 13.0f, dr::PI / 180.0f * 61.0f));
	cameras.AddCamera(light.ShareCamera());

	cube.SetPos({ 4.0f,0.0f,0.0f });
	cube2.SetPos({ 0.0f,4.0f,0.0f });

	nano.SetRootTransform(
		dx::XMMatrixRotationY(dr::PI / 2.f) *
		dx::XMMatrixTranslation(27.f, -0.56f, 1.7f)
	);
	gobber.SetRootTransform(
		dx::XMMatrixRotationY(-dr::PI / 2.f) *
		dx::XMMatrixTranslation(-8.f, 10.f, 0.f)
	);


	cube.LinkTechniques(rg);
	cube2.LinkTechniques(rg);
	light.LinkTechniques(rg);
	sponza.LinkTechniques(rg);
	gobber.LinkTechniques(rg);
	nano.LinkTechniques(rg);
	cameras.LinkTechniques(rg);

	//savingDepth = true;
}

void Scene3D::Update(float dt)
{
	cameras->BindToGraphics(wnd.Gfx());
	light.Bind(wnd.Gfx(), cameras->GetMatrix());

	cameras->Camera3DController(wnd, dt);

	if (wnd.kbd.KeyIsPressed('P'))
	{
		savingDepth  = true;
	}

}

void Scene3D::Draw(float dt)
{
	light.Submit(dr::Chan::main);
	cube.Submit(dr::Chan::main);
	sponza.Submit(dr::Chan::main);
	cube2.Submit(dr::Chan::main);
	gobber.Submit(dr::Chan::main);
	nano.Submit(dr::Chan::main);
	cameras.Submit(dr::Chan::main);

	rg.Execute(wnd.Gfx());

	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{

	// Mesh techniques window
	static dr::MP sponzeProbe{ "Sponza" };
	static dr::MP gobberProbe{ "Gobber" };
	static dr::MP nanoProbe{ "Nano" };

	// imgui window to control camera
	sponzeProbe.SpawnWindow(sponza);
	gobberProbe.SpawnWindow(gobber);
	nanoProbe.SpawnWindow(nano);

	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");
	rg.RenderWidgets(wnd.Gfx());

	rg.Reset();

	if (savingDepth)
	{
		rg.StoreDepth(wnd.Gfx(), "depth.png");
		savingDepth = false;
	}
}



