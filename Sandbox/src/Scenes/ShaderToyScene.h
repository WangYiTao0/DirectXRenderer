#pragma once

#include "Scene.h"

class ShaderToyScene :public Scene
{
public:
	ShaderToyScene(dr::Win32Window& wnd);
	virtual void Update(float dt) override;
	virtual void Draw(float dt)  override;
private:
	dr::Win32Window& wnd;

};