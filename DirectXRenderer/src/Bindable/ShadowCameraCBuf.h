#pragma once
#include "Bindable.h"
#include "ConstantBuffers.h"

namespace dr
{

	class Camera3D;

	namespace Bind
	{
		class ShadowCameraCBuf : public Bindable
		{
		protected:
			struct Transform
			{
				DirectX::XMMATRIX ViewProj;
			};
		public:
			ShadowCameraCBuf(Graphics& gfx, UINT slot = 3u);
			void Bind(Graphics& gfx) noxnd override;
			void Update(Graphics& gfx);
			void SetCamera(const Camera3D* pCamera) noexcept;
		private:
			std::unique_ptr<VertexConstantBuffer<Transform>> pVcbuf;
			const Camera3D* pCamera = nullptr;
		};
	}
}