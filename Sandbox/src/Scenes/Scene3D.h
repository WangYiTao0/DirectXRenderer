#pragma once

#include "Scene.h"

class Scene3D :public Scene
{
public:
	Scene3D(dr::Win32Window& wnd);
	virtual void Update(float dt) override;
	virtual void Draw(float dt)  override;
private:
	void SpawnImguiWindow();
private:
	dr::Win32Window& wnd;
	dr::Camera3D cam3d;
	dr::PointLight light;

	//dr::Model nano1{ wnd.Gfx(),"./asset/models/nano_textured/nanosuit.obj" };
	dr::TestPlane tp{ wnd.Gfx(),1.0 };
	dr::Model wall{ wnd.Gfx(),"./asset/textures/brick_wall/brick_wall.obj" };
	//dr::TestPlane plane;
	//dr::TestCube cube;
};