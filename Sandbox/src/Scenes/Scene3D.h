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


	dr::Model sponza{ wnd.Gfx(),".\\asset\\Models\\sponza\\sponza.obj" ,1.0f / 20.0f };
	dr::TestPlane bluePlane{ wnd.Gfx(),6.0f,{ 0.3f,0.3f,1.0f,0.0f } };
	dr::TestPlane redPlane{ wnd.Gfx(),6.0f,{ 1.0f,0.3f,0.3f,0.0f } };
};