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

	dr::Tex2D bufferA {wnd.Gfx(),"asset//textures//whiteNoise256x256.png","Texture2D_VS", 
	(float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(),"BufferA"};
	dr::Tex2D bufferB{ wnd.Gfx(),"asset//textures//whiteNoise256x256.png","Texture2D_VS",
	(float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(),"BufferB" };
	dr::Tex2D bufferC{ wnd.Gfx(),"asset//textures//whiteNoise256x256.png","Texture2D_VS",
	(float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight(),"BufferC" };
	dr::Tex2D Final { wnd.Gfx(),"Texture2D_VS", (float)wnd.Gfx().GetWidth(), (float)wnd.Gfx().GetHeight() };

};