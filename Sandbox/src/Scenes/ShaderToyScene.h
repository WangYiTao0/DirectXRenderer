#pragma once

#include "Scene.h"

class ShaderToyScene :public Scene
{
public:
	ShaderToyScene(dr::Win32Window& wnd);
	~ShaderToyScene() = default;
	virtual void Update(float dt) override;
	virtual void Draw(float dt)  override;	
	virtual void Reset()override;
private:
	dr::Win32Window& wnd;
	dr::Camera2D cam2d;
	dr::Rgph::ShaderToyRenderGraph rg{ wnd.Gfx() };

	dr::Tex2D t2d {wnd.Gfx(),"asset//textures//brickwall.jpg","Texture2D_VS", "Texture2D_PS",(float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight()};

};