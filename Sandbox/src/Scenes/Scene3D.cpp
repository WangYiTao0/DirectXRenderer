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
}

void Scene3D::Update(float dt)
{
	wnd.Gfx().SetCamera(cam3d.GetMatrix());
	light.Bind(wnd.Gfx(), cam3d.GetMatrix());



}

void Scene3D::Draw(float dt)
{

	nano.Draw(wnd.Gfx());
	light.Draw(wnd.Gfx());

	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{
	// imgui window to control camera
	cam3d.SpawnControlWindow();
	light.SpawnControlWindow();
	nano.ShowWindow();
	ShowRawInputWindow();
}

void Scene3D::ShowRawInputWindow()
{
	while (const auto d = wnd.mouse.ReadRawDelta())
	{
		x += d->x;
		y += d->y;
	}
	if (ImGui::Begin("Raw Input"))
	{
		ImGui::Text("Tally: (%d,%d)", x, y);
		ImGui::Text("Cursor: %s", wnd.CursorEnabled() ? "enabled" : "disabled");
	}
	ImGui::End();
}

