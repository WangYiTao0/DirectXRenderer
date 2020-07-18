#pragma once
#include <string>
#include <DirectXMath.h>
#include "Core/Win32Window.h"


namespace dr
{
	class Graphics;

	class Camera2D
	{
	public:
		Camera2D(Graphics& gfx,std::string name);
		void SetOrthoProjection(float width, float height, float nearZ, float farZ);
		const DirectX::XMMATRIX& GetOrthoMatrix() const noexcept;
		DirectX::XMMATRIX GetWorldMatrix()const noexcept;
		void BindToGraphics(Graphics& gfx) const;
		void Camera2DController(Win32Window& win, float dt);
	private:
		DirectX::XMMATRIX orthoMatrix;
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 rollPitchYaw;
	
	};
}