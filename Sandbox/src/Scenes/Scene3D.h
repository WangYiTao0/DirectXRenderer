#pragma once

#include "Scene.h"


class Scene3D :public Scene
{
public:
	Scene3D(dr::Win32Window& wnd);
	~Scene3D() = default;
	virtual void Update(float dt) override;
	virtual void Draw(float dt)  override;
	virtual void Reset()override;
private:
	void SpawnImguiWindow();
private:
	dr::Win32Window& wnd;
	dr::CameraContainer cameras;
	dr::Camera2D cam2d;
	dr::PointLight light;


	dr::Rgph::BlurOutlineRenderGraph rg{ wnd.Gfx() };
	dr::TestCube cube{ wnd.Gfx(),4.0f };
	dr::TestCube cube2{ wnd.Gfx(),4.0f };
	dr::Model sponza{ wnd.Gfx(),"asset\\Models\\sponza\\sponza.obj",1.0f / 20.0f };
	//dr::Model gobber{ wnd.Gfx(),"asset\\Models\\gobber\\GoblinX.obj",4.0f };
	//dr::Model nano{ wnd.Gfx(),"asset\\Models\\nano_textured\\nanosuit.obj",2.0f };
	//dr::Model sponza{ wnd.Gfx(),".\\asset\\Models\\sponza\\sponza.obj" ,1.0f / 20.0f };

	//dr::Tex2D shadowViewTexture{ wnd.Gfx(),"Texture2D_VS", "ShadowLiner_PS",200,200, };

	bool savingDepth = false;
};