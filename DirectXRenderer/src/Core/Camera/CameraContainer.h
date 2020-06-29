#pragma once
#include <vector>
#include <memory>

namespace dr
{

	class Camera3D;
	class Graphics;

	namespace Rgph
	{
		class RenderGraph;
	}

	class CameraContainer
	{
	public:
		void SpawnWindow(Graphics& gfx);
		void Bind(Graphics& gfx);
		void AddCamera(std::unique_ptr<Camera3D> pCam);
		Camera3D* operator->();
		~CameraContainer();

		void LinkTechniques(Rgph::RenderGraph& rg);
		void Submit() const;
	private:
		Camera3D& GetControlledCamera();
	private:
		std::vector<std::unique_ptr<Camera3D>> cameras;
		int active = 0;
		int controlled = 0;
	};

}