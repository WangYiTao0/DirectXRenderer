#pragma once

#include <myRenderer.h>
#include <string>

class Scene
{
public:
	Scene(const std::string& name)
		:
		name(name)
	{}
	virtual void Update(float dt) = 0;
	virtual void Draw(float dt) = 0;
	virtual void DrawDepth() {};
	virtual ~Scene() = default;
	const std::string& GetName() const
	{
		return name;
	}
private:
	const std::string name;
};