#pragma once

#include "Scene.h"

class Scene3D :public Scene
{
public:
	Scene3D(dr::Graphics& gfx);
	virtual void Update(float dt) override;
	virtual void Draw()  override;
private:
	dr::Graphics& gfx;

};