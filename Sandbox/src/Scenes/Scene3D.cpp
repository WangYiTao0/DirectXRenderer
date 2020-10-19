#include <myRenderer.h>
#include <memory>
#include "Scene3D.h"
#include "imgui.h"
#include "TestModelProbe.h"

namespace dx = DirectX;

Scene3D::Scene3D(dr::Win32Window& wnd)
	:
	wnd(wnd),
	light(wnd.Gfx(), { 10.0f,5.0f,0.0f }),
	Scene("Scene3D")
{
	cameras.AddCamera(std::make_unique<dr::Camera3D>(wnd.Gfx(), "A", dx::XMFLOAT3{ -13.5f,6.0f,3.5f }, 0.0f, dr::PI / 2.0f));
	cameras.AddCamera(std::make_unique<dr::Camera3D>(wnd.Gfx(), "B", dx::XMFLOAT3{ -13.5f,28.8f,-6.4f }, dr::PI / 180.0f * 13.0f, dr::PI / 180.0f * 61.0f));
	cameras.AddCamera(light.ShareCamera());

	//cube.SetPos({ 10.0f,5.0f,6.0f });
	//cube2.SetPos({ 10.0f,5.0f,14.0f });

	nano.SetRootTransform(dx::XMMatrixRotationY(dr::PI / 2.f) *
		dx::XMMatrixTranslation(27.f, -0.56f, 1.7f) * 
		dx::XMMatrixScaling(0.3f, 0.3f, 0.3f)
	);
	//gobber.SetRootTransform(
	//	dx::XMMatrixRotationY(-dr::PI / 2.f) *
	//	dx::XMMatrixTranslation(-8.f, 10.f, 0.f)
	//);


	light.LinkTechniques(rg);
	sponza.LinkTechniques(rg);
	cameras.LinkTechniques(rg);
	nano.LinkTechniques(rg);
	//cube.LinkTechniques(rg);
	//cube2.LinkTechniques(rg);
	//gobber.LinkTechniques(rg);

	rg.BindShadowCamera(*light.ShareCamera());
}

void Scene3D::Update(float dt)
{
	light.Bind(wnd.Gfx(), cameras->GetMatrix());
	rg.BindMainCamera(cameras.GetActiveCamera());

	cameras->Camera3DController(wnd, dt);

	if (wnd.kbd.KeyIsPressed('P'))
	{
		savingDepth  = true;
	}

}

void Scene3D::Draw(float dt)
{
	using namespace dr;

	light.Submit(dr::Chan::main);
	cameras.Submit(dr::Chan::main);
	sponza.Submit(dr::Chan::main);
	nano.Submit(dr::Chan::main);
	
	/*cube.Submit(dr::Chan::main);
	cube2.Submit(dr::Chan::main);
	gobber.Submit(dr::Chan::main);
	*/

	sponza.Submit(Chan::shadow);
	nano.Submit(Chan::shadow);
	//cube.Submit(Chan::shadow);
	//cube2.Submit(Chan::shadow);
	//gobber.Submit(Chan::shadow);

	rg.Execute(wnd.Gfx());

	if (savingDepth)
	{
		rg.DumpShadowMap(wnd.Gfx(), "shadow.png");
		savingDepth = false;
	}

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
	cameras.SpawnWindow(wnd.Gfx());
	light.SpawnControlWindow();
	sponzeProbe.SpawnWindow(sponza);
	nanoProbe.SpawnWindow(nano);
	
	/*
	gobberProbe.SpawnWindow(gobber);
	cube.SpawnControlWindow(wnd.Gfx(), "Cube 1");
	cube2.SpawnControlWindow(wnd.Gfx(), "Cube 2");
	*/
	rg.OnImGuiRender(wnd.Gfx());

	rg.Reset();
}



