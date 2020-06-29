#pragma once
#include <Core/Graphics.h>
#include <Core/Win32Window.h>
namespace dr
{
	class Camera3D
	{
	public:
		Camera3D(DirectX::XMFLOAT3 homePos = { 0.0f,0.0f,0.0f }, 
			float homePitch = 0.0f, float homeYaw = 0.0f) noexcept;
		DirectX::XMMATRIX GetMatrix() const noexcept;
		void SpawnControlWindow() noexcept;
		void Camera3DController(Win32Window& wnd, float dt);
		void Reset() noexcept;
		void Rotate(float dx, float dy) noexcept;
		void Translate(DirectX::XMFLOAT3 translation) noexcept;
		DirectX::XMFLOAT3 GetPos() const noexcept;
	private:
		DirectX::XMFLOAT3 homePos;
		float homePitch;
		float homeYaw;
		DirectX::XMFLOAT3 pos;
		float pitch;
		float yaw;
		static constexpr float travelSpeed = 12.0f;
		static constexpr float rotationSpeed = 0.004f;
	};
}