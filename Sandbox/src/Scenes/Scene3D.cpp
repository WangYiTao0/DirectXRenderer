#include <myRenderer.h>
#include <memory>
#include "Scene3D.h"

Scene3D::Scene3D(dr::Win32Window& wnd)
	:
	wnd(wnd),
	light(wnd.Gfx()),
	Scene("Scene3D")
{
	class Factory
	{
	public:
		Factory(dr::Graphics& gfx)
			:
			gfx(gfx)
		{}
		std::unique_ptr<dr::Drawable> operator()()
		{
			const DirectX::XMFLOAT3 mat = { cdist(rng),cdist(rng),cdist(rng) };
			return std::make_unique<dr::Box>(
				gfx, rng, adist, ddist,
				odist, rdist, bdist, mat
				);
		}
	private:
		dr::Graphics& gfx;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_real_distribution<float> adist{ 0.0f,dr::PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,dr::PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,dr::PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f,1.0f };
	};

	drawables.reserve(nDrawables);
	std::generate_n(std::back_inserter(drawables), nDrawables,
		Factory{ wnd.Gfx() });

}

void Scene3D::Update(float dt)
{
	wnd.Gfx().SetCamera(cam3d.GetMatrix());
	light.Bind(wnd.Gfx());

}

void Scene3D::Draw(float dt)
{

	for (auto& d : drawables)
	{
		d->Update(wnd.kbd.KeyIsPressed(VK_SPACE) ? 0.0f : dt);
		d->Draw(wnd.Gfx());
	}

	light.Draw(wnd.Gfx());

	///ImguiWidow
	SpawnImguiWindow();
}

void Scene3D::SpawnImguiWindow()
{
	// imgui window to control camera
	cam3d.SpawnControlWindow();
	light.SpawnControlWindow();
}
