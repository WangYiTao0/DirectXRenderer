#pragma once
#include <Core/Graphics.h>
#include <Core/Win32Window.h>
namespace dr
{
	class Camera3D
	{
	public:
		Camera3D() noexcept;
		DirectX::XMMATRIX GetMatrix() const noexcept;
		void SpawnControlWindow() noexcept;
		void Camera3DController(Win32Window& wnd, float dt);
		void Reset() noexcept;
		void Rotate(float dx, float dy) noexcept;
		void Translate(DirectX::XMFLOAT3 translation) noexcept;
	private:
		DirectX::XMFLOAT3 pos;
		float pitch;
		float yaw;
		static constexpr float travelSpeed = 12.0f;
		static constexpr float rotationSpeed = 0.004f;
	};
}