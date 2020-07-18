#include "drpch.h"
#include "TransformCbuf.h"

namespace dr
{
	namespace Bind
	{
		TransformCbuf::TransformCbuf(Graphics& gfx, UINT slot)
		{
			if (!pVcbuf)
			{
				pVcbuf = std::make_unique<VertexConstantBuffer<Transforms>>(gfx, slot);
			}
		}


		void TransformCbuf::Bind(Graphics& gfx) noxnd
		{
			INFOMAN_NOHR(gfx);
			GFX_THROW_INFO_ONLY(UpdateBindImpl(gfx, GetTransforms(gfx)));
		}


		void TransformCbuf::InitializeParentReference(const Drawable& parent) noexcept
		{
			pParent = &parent;
		}

		std::unique_ptr<dr::Bind::CloningBindable> TransformCbuf::Clone() const noexcept
		{
			return std::make_unique<TransformCbuf>(*this);
		}


		void TransformCbuf::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noxnd
		{
			assert(pParent != nullptr);
			pVcbuf->Update(gfx, tf);
			pVcbuf->Bind(gfx);
		}

		TransformCbuf::Transforms TransformCbuf::GetTransforms(Graphics& gfx) noxnd
		{
			assert(pParent != nullptr);
			const auto model = pParent->GetTransformXM();
			const auto modelView = model * gfx.GetCamera3D();
			return {
			DirectX::XMMatrixTranspose(model),
			DirectX::XMMatrixTranspose(modelView),
			DirectX::XMMatrixTranspose(
				modelView *
				gfx.GetProjection()
				)
			};
		}

		std::unique_ptr<VertexConstantBuffer<TransformCbuf::Transforms>> TransformCbuf::pVcbuf;
	}
}
