#include "drpch.h"
#include "Mesh.h"
#include "imgui/imgui.h"
#include "Core/Surface.h"
#include "CommonTool/DrMath.h"

namespace dx = DirectX;

namespace dr
{
	// Mesh
	Mesh::Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale) noxnd
		:
	Drawable(gfx, mat, mesh, scale)
	{}

	void Mesh::Submit(size_t channels, dx::FXMMATRIX accumulatedTranform) const noxnd
	{
		dx::XMStoreFloat4x4(&transform, accumulatedTranform);
		Drawable::Submit(channels);
	}

	DirectX::XMMATRIX Mesh::GetTransformXM() const noexcept
	{
		return DirectX::XMLoadFloat4x4(&transform);
	}
}