#include "drpch.h"
#include "CameraContainer.h"
#include "imgui/imgui.h"
#include "Camera3D.h"
#include "Core/Graphics.h"
#include "Jobber/RenderGraph.h"

namespace dr
{

	void CameraContainer::SpawnWindow(Graphics& gfx)
	{
		if (ImGui::Begin("Cameras"))
		{
			if (ImGui::BeginCombo("Active Camera", cameras[selected]->GetName().c_str()))
			{
				for (int i = 0; i < std::size(cameras); i++)
				{
					const bool isSelected = i == selected;
					if (ImGui::Selectable(cameras[i]->GetName().c_str(), isSelected))
					{
						selected = i;
					}
				}
				ImGui::EndCombo();
			}

			GetCamera().SpawnControlWidgets(gfx);
		}
		ImGui::End();
	}

	void CameraContainer::Bind(Graphics& gfx)
	{
		gfx.SetCamera(GetCamera().GetMatrix());
	}

	void CameraContainer::AddCamera(std::unique_ptr<Camera3D> pCam)
	{
		cameras.push_back(std::move(pCam));
	}

	Camera3D& CameraContainer::GetCamera()
	{
		return *cameras[selected];
	}

	CameraContainer::~CameraContainer()
	{}

	void CameraContainer::LinkTechniques(Rgph::RenderGraph& rg)
	{
		for (auto& pcam : cameras)
		{
			pcam->LinkTechniques(rg);
		}
	}

	void CameraContainer::Submit() const
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			if (i != selected)
			{
				cameras[i]->Submit();
			}
		}
	}

}