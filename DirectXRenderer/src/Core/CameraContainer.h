#pragma once
#include <vector>
#include <memory>

namespace dr
{

	class Camera3D;
	class Graphics;

	class CameraContainer
	{
	public:
		void SpawnWindow();
		void Bind(Graphics& gfx);
		void AddCamera(std::unique_ptr<Camera3D> pCam);
		Camera3D& GetCamera();
		~CameraContainer();
	private:
		std::vector<std::unique_ptr<Camera3D>> cameras;
		int selected = 0;
	};

}