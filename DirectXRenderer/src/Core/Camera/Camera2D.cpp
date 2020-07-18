#include "drpch.h"
#include "Camera2D.h"

namespace dx =  DirectX;

namespace dr
{
	Camera2D::Camera2D(Graphics& gfx, std::string name)
	{
		pos = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
		rollPitchYaw = dx::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	void Camera2D::SetOrthoProjection(float width, float height, float nearZ, float farZ)
	{
		orthoMatrix = dx::XMMatrixOrthographicOffCenterLH(0.0f, width, height, 0.0f, nearZ, farZ);
	}

	const DirectX::XMMATRIX& Camera2D::GetOrthoMatrix() const noexcept
	{
		return orthoMatrix;
	}

	DirectX::XMMATRIX Camera2D::GetWorldMatrix() const noexcept
	{
		dx::XMMATRIX translationOffsetMatrix = dx::XMMatrixTranslation(-pos.x, -pos.y, 0.0f); //z component irrelevant for 2d camera
		dx::XMMATRIX camRotationMatrix = dx::XMMatrixRotationRollPitchYaw(rollPitchYaw.x, rollPitchYaw.y, rollPitchYaw.z);
		dx::XMMATRIX worldMatrix = camRotationMatrix * translationOffsetMatrix;

		return worldMatrix;
	}

	void Camera2D::BindToGraphics(Graphics& gfx) const
	{
		gfx.SetCamera2D(GetWorldMatrix());
		gfx.SetOrthProjection(GetOrthoMatrix());

	}

	void Camera2D::Camera2DController(Win32Window& win, float dt)
	{

	}

}