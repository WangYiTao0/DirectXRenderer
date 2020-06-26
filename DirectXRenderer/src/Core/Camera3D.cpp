#include "drpch.h"
#include "Camera3D.h"
#include "imgui.h"
#include "CommonTool/DrMath.h"

namespace dr
{
	namespace dx = DirectX;

	Camera3D::Camera3D() noexcept
	{
		Reset();
	}

	DirectX::XMMATRIX Camera3D::GetMatrix() const noexcept
	{

		using namespace dx;

		const dx::XMVECTOR forwardBaseVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		// apply the camera rotations to a base vector
		const auto lookVector = XMVector3Transform(forwardBaseVector,
			XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f)
		);
		// generate camera transform (applied to all objects to arrange them relative
		// to camera position/orientation in world) from cam position and direction
		// camera "top" always faces towards +Y (cannot do a barrel roll)
		const auto camPosition = XMLoadFloat3(&pos);
		const auto camTarget = camPosition + lookVector;
		return XMMatrixLookAtLH(camPosition, camTarget, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	}

	void Camera3D::SpawnControlWindow() noexcept
	{
		if (ImGui::Begin("Camera3D"))
		{
			ImGui::Text("Position");
			ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f");
			ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f");
			ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f");
			ImGui::Text("Orientation");
			ImGui::SliderAngle("Pitch", &pitch, 0.995f * -90.0f, 0.995f * 90.0f);
			ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
			if (ImGui::Button("Reset"))
			{
				Reset();
			}
		}
		ImGui::End();
	}

	void Camera3D::Camera3DController(Win32Window& wnd,float dt)
	{
		if (!wnd.CursorEnabled())
		{
			if (wnd.kbd.KeyIsPressed('W'))
			{
				Translate({ 0.0f,0.0f,dt });
			}
			if (wnd.kbd.KeyIsPressed('A'))
			{
				Translate({ -dt,0.0f,0.0f });
			}
			if (wnd.kbd.KeyIsPressed('S'))
			{
				Translate({ 0.0f,0.0f,-dt });
			}
			if (wnd.kbd.KeyIsPressed('D'))
			{
				Translate({ dt,0.0f,0.0f });
			}
			if (wnd.kbd.KeyIsPressed('R'))
			{
				Translate({ 0.0f,dt,0.0f });
			}
			if (wnd.kbd.KeyIsPressed('F'))
			{
				Translate({ 0.0f,-dt,0.0f });
			}
		}

		while (const auto delta = wnd.mouse.ReadRawDelta())
		{
			if (!wnd.CursorEnabled())
			{
				Rotate((float)delta->x, (float)delta->y);
			}
		}
	}


	void Camera3D::Reset() noexcept
	{
		pos = { 0.0f,7.5f,-18.0f };
		pitch = 0.0f;
		yaw = 0.0f;
	}

	void Camera3D::Rotate(float dx, float dy) noexcept
	{
		yaw = wrap_angle(yaw + dx * rotationSpeed);
		pitch = std::clamp(pitch + dy * rotationSpeed, -PI / 2.0f, PI / 2.0f);
	}

	void Camera3D::Translate(DirectX::XMFLOAT3 translation) noexcept
	{
		dx::XMStoreFloat3(&translation, dx::XMVector3Transform(
			dx::XMLoadFloat3(&translation),
			dx::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) *
			dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
		));
		pos = {
			pos.x + translation.x,
			pos.y + translation.y,
			pos.z + translation.z
		};
	}


}
