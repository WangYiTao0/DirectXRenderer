#include "drpch.h"
#include "SolidSphere.h"
#include "Bindable/BindableCommon.h"
#include "Debug/ThrowMacros.h"
#include "Core/Vertex.h"
#include "Geometry/Sphere.h"

namespace dr
{
	using namespace Bind;

	SolidSphere::SolidSphere(Graphics& gfx, float radius)
	{
		namespace dx = DirectX;

		auto model = Sphere::Make();

		model.Transform(dx::XMMatrixScaling(radius, radius, radius));
		AddBind(std::make_shared<Bind::VertexBuffer>(gfx, model.vertices));
		AddBind(std::make_shared<IndexBuffer>(gfx, model.indices));

		auto pvs = std::make_shared<VertexShader>(gfx, "./asset/shader/cso/Solid_vs.cso");
		auto pvsbc = pvs->GetBytecode();
		AddBind(std::move(pvs));

		AddBind(std::make_shared<PixelShader>(gfx, "./asset/shader/cso/Solid_ps.cso"));

		struct PSColorConstant
		{
			dx::XMFLOAT3 color = { 1.0f,1.0f,1.0f };
			float padding;
		} colorConst;
		AddBind(std::make_shared<PixelConstantBuffer<PSColorConstant>>(gfx, colorConst));

		AddBind(std::make_shared<InputLayout>(gfx, model.vertices.GetLayout(), pvsbc));

		AddBind(std::make_shared<Topology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		AddBind(std::make_shared<TransformCbuf>(gfx, *this));
	}

	void SolidSphere::Update(float dt) noexcept {}

	void SolidSphere::SetPos(DirectX::XMFLOAT3 pos) noexcept
	{
		this->pos = pos;
	}

	DirectX::XMMATRIX SolidSphere::GetTransformXM() const noexcept
	{
		return DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	}

}