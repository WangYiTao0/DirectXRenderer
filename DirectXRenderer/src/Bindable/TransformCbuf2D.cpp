#include "drpch.h"
#include "TransformCbuf2D.h"

namespace dr
{
	namespace Bind
	{
		TransformCbuf2D::TransformCbuf2D(Graphics& gfx, UINT slot)
		{
			if (!pVcbuf)
			{
				pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx, slot);
			}
		}


		void TransformCbuf2D::Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(UpdateBindImpl(gfx, GetTransforms(gfx)));
		}


		void TransformCbuf2D::InitializeParentReference(const Drawable& parent) noexcept
		{
			pParent = &parent;
		}

		std::unique_ptr<dr::Bind::CloningBindable> TransformCbuf2D::Clone() const noexcept
		{
			return std::make_unique<TransformCbuf2D>(*this);
		}


		void TransformCbuf2D::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noxnd
		{
			assert(pParent != nullptr);
			pVcbuf->Update(gfx, tf);
			pVcbuf->Bind(gfx);
		}

		TransformCbuf2D::Transforms TransformCbuf2D::GetTransforms(Graphics& gfx) noxnd
		{
			assert(pParent != nullptr);
			const auto model = pParent->GetTransformXM();
			const auto modelView = model * gfx.GetCamera2D();
			return {
			DirectX::XMMatrixTranspose(model),
			DirectX::XMMatrixTranspose(modelView),
			DirectX::XMMatrixTranspose(
				modelView *
				gfx.GetOrthProjection()
				)
			};
		}

		std::unique_ptr<VertexConstantBuffer<TransformCbuf2D::Transforms>> TransformCbuf2D::pVcbuf;
	}
}
