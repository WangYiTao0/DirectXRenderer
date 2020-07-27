#pragma once
#include "Scene.h"

class DeferredScene : public Scene 
{
public:
	DeferredScene(dr::Win32Window& wnd);
	~DeferredScene() = default;
	virtual void Update(float dt) override;
	virtual void Draw(float dt)  override;
	virtual void Reset()override;

private:
	dr::Win32Window& wnd;

	dr::CameraContainer cameras;
	dr::PointLight light;

};