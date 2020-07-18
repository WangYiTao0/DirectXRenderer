#pragma once
#include "ConstantBuffers.h"
#include "Drawable/Drawable.h"
#include <DirectXMath.h>

namespace dr
{
	namespace Bind
	{
		class TransformCbuf2D : public CloningBindable
		{
		protected:
			struct Transforms
			{
				DirectX::XMMATRIX model;
				DirectX::XMMATRIX modelView;
				DirectX::XMMATRIX modelViewProj;
			};
		public:
			TransformCbuf2D(Graphics& gfx, UINT slot = 0u);
			void Bind(Graphics& gfx) noxnd override;
			void InitializeParentReference(const Drawable& parent) noexcept override;
			std::unique_ptr<CloningBindable> Clone() const noexcept override;
		protected:
			void UpdateBindImpl(Graphics& gfx, const Transforms& tf) noxnd;
			Transforms GetTransforms(Graphics& gfx) noxnd;
		private:
			static std::unique_ptr<VertexConstantBuffer<Transforms>> pVcbuf;
			const Drawable* pParent = nullptr;
		};
	}
}