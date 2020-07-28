#include "drpch.h"
#include "Tex2D.h"
#include "Geometry/Plane.h"
#include "Bindable/BindableCommon.h"
#include "Imgui/imgui.h"
#include "Jobber/Graphlib/Channels.h"

namespace dr
{

	Tex2D::Tex2D(Graphics& gfx, std::string path, std::string vs_name,  float width, float height)
	{
		using namespace Bind;
		namespace dx = DirectX;

		auto model = Plane::Make2DTextured();
		model.Transform(dx::XMMatrixScaling(width,height, 1.0f));
		const auto geometryTag = "$plane." + std::to_string(width);
		pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
		pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
		pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		{
			Technique shade2D("Shade2D", Chan::Orth);
			
			Step only("BufferA");

			only.AddBindable(Texture::Resolve(gfx, path,1));
			only.AddBindable(Texture::Resolve(gfx, "asset//textures//rgbaNoise.png", 2));
			

			auto pvs = VertexShader::Resolve(gfx, vs_name);
			only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
			only.AddBindable(std::move(pvs));

			only.AddBindable(std::make_shared<TransformCbuf2D>(gfx));
			only.AddBindable(Rasterizer::Resolve(gfx, false));
			//only.AddBindable(Blender::Resolve(gfx, true));

			shade2D.AddStep(std::move(only));
			
			AddTechnique(std::move(shade2D));
		}
	}

	Tex2D::Tex2D(Graphics& gfx, std::string vs_name, float width, float height)
	{
		using namespace Bind;
		namespace dx = DirectX;

		auto model = Plane::Make2DTextured();
		model.Transform(dx::XMMatrixScaling(width, height, 1.0f));
		const auto geometryTag = "$plane." + std::to_string(width);
		pVertices = VertexBuffer::Resolve(gfx, geometryTag, model.vertices);
		pIndices = IndexBuffer::Resolve(gfx, geometryTag, model.indices);
		pTopology = Topology::Resolve(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


		// setup other common fullscreen bindables

		{
			Technique shade2D("Shade2D", Chan::Orth);

			Step only("texture2D");

			auto pvs = VertexShader::Resolve(gfx, vs_name);
			only.AddBindable(InputLayout::Resolve(gfx, model.vertices.GetLayout(), *pvs));
			only.AddBindable(std::move(pvs));

			only.AddBindable(std::make_shared<TransformCbuf2D>(gfx));

			only.AddBindable(Rasterizer::Resolve(gfx, false));
			//only.AddBindable(Blender::Resolve(gfx, true));

			shade2D.AddStep(std::move(only));

			AddTechnique(std::move(shade2D));
		}
	}

	void Tex2D::SetPos(DirectX::XMFLOAT3 pos) noexcept
	{
		this->pos = pos;
	}

	void Tex2D::SetRotation(float roll, float pitch, float yaw) noexcept
	{
		this->roll = roll;
		this->pitch = pitch;
		this->yaw = yaw;
	}

	DirectX::XMMATRIX Tex2D::GetTransformXM() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(roll, pitch, yaw) *
			DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	}

	void Tex2D::SpawnControlWindow(Graphics& gfx, const std::string& name) noexcept
	{
		//if (ImGui::Begin(name.c_str()))
		//{
		//	ImGui::Text("Position");
		//	ImGui::SliderFloat("X", &pos.x, -80.0f, 80.0f, "%.1f");
		//	ImGui::SliderFloat("Y", &pos.y, -80.0f, 80.0f, "%.1f");
		//	ImGui::SliderFloat("Z", &pos.z, -80.0f, 80.0f, "%.1f");
		//	ImGui::Text("Orientation");
		//	ImGui::SliderAngle("Roll", &roll, -180.0f, 180.0f);
		//	ImGui::SliderAngle("Pitch", &pitch, -180.0f, 180.0f);
		//	ImGui::SliderAngle("Yaw", &yaw, -180.0f, 180.0f);
		//	ImGui::Text("Shading");
		//	auto pBlender = QueryBindable<Bind::Blender>();
		//	float factor = pBlender->GetFactor();
		//	ImGui::SliderFloat("Translucency", &factor, 0.0f, 1.0f);
		//	pBlender->SetFactor(factor);
		//}
		//ImGui::End();
	}

}