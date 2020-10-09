#include "drpch.h"
#include "ShadowCameraCBuf.h"
#include "Core/Camera/Camera3D.h"

namespace dx = DirectX;
namespace dr
{
	namespace Bind
	{
		ShadowCameraCBuf::ShadowCameraCBuf(Graphics& gfx, UINT slot)
			:
			pVcbuf{ std::make_unique<VertexConstantBuffer<Transform>>(gfx,slot) }
		{}
		void ShadowCameraCBuf::Bind(Graphics& gfx) noxnd
		{
			pVcbuf->Bind(gfx);
		}
		void ShadowCameraCBuf::Update(Graphics& gfx)
		{
			const auto pos = pCamera->GetPos();
			const Transform t{
				dx::XMMatrixTranspose(
					dx::XMMatrixTranslation(-pos.x,-pos.y,-pos.z)
				)
			};
			pVcbuf->Update(gfx, t);
		}
		void ShadowCameraCBuf::SetCamera(const Camera3D* p) noexcept
		{
			pCamera = p;
		}
	}

}
