#include "drpch.h"
#include "TransformPsCbuf.h"

namespace dr
{
	//namespace Bind
	//{
	//	TransformPsCbuf::TransformPsCbuf(Graphics& gfx, const Drawable& parent, UINT slotV, UINT slotP)
	//		:
	//		TransformCbuf(gfx, parent, slotV)
	//	{
	//		if (!pPcbuf)
	//		{
	//			pPcbuf = std::make_unique<PixelConstantBuffer<Transforms>>(gfx, slotP);
	//		}
	//	}

	//	void Bind::TransformPsCbuf::Bind(Graphics& gfx) noexcept
	//	{
	//		const auto tf = GetTransforms(gfx);
	//		TransformCbuf::UpdateBindImpl(gfx, tf);
	//		UpdateBindImpl(gfx, tf);
	//	}

	//	void TransformPsCbuf::UpdateBindImpl(Graphics& gfx, const Transforms& tf) noexcept
	//	{
	//		pPcbuf->Update(gfx, tf);
	//		pPcbuf->Bind(gfx);
	//	}

	//	std::unique_ptr<PixelConstantBuffer<TransformCbuf::Transforms>> TransformPsCbuf::pPcbuf;
	//}
}
