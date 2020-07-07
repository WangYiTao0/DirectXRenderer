#include "drpch.h"
#include "Camera3D.h"
#include "imgui.h"
#include "CommonTool/DrMath.h"
#include "Core/Graphics.h"

namespace dr
{
	namespace dx = DirectX;

	Camera3D::Camera3D(Graphics& gfx, std::string name,
		DirectX::XMFLOAT3 homePos, float homePitch, 
		float homeYaw,bool tethered) noexcept
		:
		name(std::move(name)),
		homePos(homePos),
		homePitch(homePitch),
		homeYaw(homeYaw),
		proj(gfx, 1.0f, 9.0f / 16.0f, 0.5f, 400.0f),
		indicator(gfx),
		tethered(tethered)
	{
		if (tethered)
		{
			pos = homePos;
			indicator.SetPos(pos);
			proj.SetPos(pos);
		}
		Reset(gfx);
	}
	void Camera3D::BindToGraphics(Graphics& gfx) const
	{
		gfx.SetCamera(GetMatrix());
		gfx.SetProjection(proj.GetMatrix());
	}

	DirectX::XMMATRIX Camera3D::GetMatrix() const noexcept
	{

		using namespace dx;

		const dx::XMVECTOR forwardBaseVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		// apply the camera rotations to a base vector
		const auto lookVector = XMVector3Transform(forwardBaseVector,XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));
		// generate camera transform (applied to all objects to arrange them relative
		// to camera position/orientation in world) from cam position and direction
		// camera "top" always faces towards +Y (cannot do a barrel roll)
		const auto camPosition = XMLoadFloat3(&pos);
		const auto camTarget = camPosition + lookVector;
		return XMMatrixLookAtLH(camPosition, camTarget, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
	}

	DirectX::XMMATRIX Camera3D::GetProjection() const noexcept
	{
		return proj.GetMatrix();
	}

	void Camera3D::SpawnControlWidgets(Graphics& gfx) noexcept
	{
		bool rotDirty = false;
		bool posDirty = false;
		const auto dcheck = [](bool d, bool& carry) { carry = carry || d; };
		if (!tethered)
		{
			ImGui::Text("Position");
			dcheck(ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f"), posDirty);
			dcheck(ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f"), posDirty);
			dcheck(ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f"), posDirty);
		}
		ImGui::Text("Orientation");
		dcheck(ImGui::SliderAngle("Pitch", &pitch, 0.995f * -90.0f, 0.995f * 90.0f), rotDirty);
		dcheck(ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f), rotDirty);
		proj.RenderWidgets(gfx);
		ImGui::Checkbox("Camera Indicator", &enableCameraIndicator);
		ImGui::Checkbox("Frustum Indicator", &enableFrustumIndicator);
		if (ImGui::Button("Reset"))
		{
			Reset(gfx);
		}

		if (rotDirty)
		{
			const dx::XMFLOAT3 angles = { pitch,yaw,0.0f };
			indicator.SetRotation(angles);
			proj.SetRotation(angles);
		}
		if (posDirty)
		{
			indicator.SetPos(pos);
			proj.SetPos(pos);
		}
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


	void Camera3D::Reset(Graphics& gfx) noexcept
	{
		if (!tethered)
		{
			pos = homePos;
			indicator.SetPos(pos);
			proj.SetPos(pos);
		}
		pos = homePos;
		pitch = homePitch;
		yaw = homeYaw;

		const dx::XMFLOAT3 angles = { pitch,yaw,0.0f };
		indicator.SetRotation(angles);
		proj.SetRotation(angles);
		proj.Reset(gfx);
	}

	void Camera3D::Rotate(float dx, float dy) noexcept
	{
		yaw = wrap_angle(yaw + dx * rotationSpeed);
		pitch = std::clamp(pitch + dy * rotationSpeed, -PI / 2.0f, PI / 2.0f);
		const dx::XMFLOAT3 angles = { pitch,yaw,0.0f };
		indicator.SetRotation(angles);
		proj.SetRotation(angles);
	}

	void Camera3D::Translate(DirectX::XMFLOAT3 translation) noexcept
	{
		if (!tethered)
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
			indicator.SetPos(pos);
			proj.SetPos(pos);
		}
	}

	DirectX::XMFLOAT3 Camera3D::GetPos() const noexcept
	{
		return pos;
	}

	void Camera3D::SetPos(const DirectX::XMFLOAT3& pos) noexcept
	{
		this->pos = pos;
		indicator.SetPos(pos);
		proj.SetPos(pos);
	}

	const std::string& Camera3D::GetName() const noexcept
	{
		return name;
	}

	void Camera3D::LinkTechniques(Rgph::RenderGraph& rg)
	{
		indicator.LinkTechniques(rg);
		proj.LinkTechniques(rg);
	}

	void Camera3D::Submit(size_t channels) const
	{
		if (enableCameraIndicator)
		{
			indicator.Submit(channels);
		}
		if (enableFrustumIndicator)
		{
			proj.Submit(channels);
		}
	}
}
