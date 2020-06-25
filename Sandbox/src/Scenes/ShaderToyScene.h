#pragma once

#include "Scene.h"

class ShaderToyScene :public Scene
{
public:
	ShaderToyScene(dr::Graphics& gfx);
	virtual void Update(float dt) override;
	virtual void Draw()  override;
private:
	dr::Graphics& gfx;

};