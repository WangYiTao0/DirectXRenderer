#pragma once
#include "Core/Graphics.h"
#include "Drawable/Drawable.h"
#include "Debug/ThrowMacros.h"

struct aiMesh;
namespace dr
{
	class Material;

	class Mesh : public Drawable
	{
	public:
		Mesh(Graphics& gfx, const Material& mat, const aiMesh& mesh, float scale = 1.0f) noxnd;
		DirectX::XMMATRIX GetTransformXM() const noexcept override;
		void Submit(size_t channels, DirectX::FXMMATRIX accumulatedTranform) const noxnd;
	private:
		mutable DirectX::XMFLOAT4X4 transform;
	};
}