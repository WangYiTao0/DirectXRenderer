#pragma once
#include "ConstantBuffers.h"
#include "Drawable/Drawable.h"
#include <DirectXMath.h>

namespace dr
{
	namespace Bind
	{
		class TransformCbuf : public Bindable
		{
		public:
			TransformCbuf(Graphics& gfx, const Drawable& parent);
			void Bind(Graphics& gfx) noexcept override;
		private:
			VertexConstantBuffer<DirectX::XMMATRIX> vcbuf;
			const Drawable& parent;
		};
	}
}