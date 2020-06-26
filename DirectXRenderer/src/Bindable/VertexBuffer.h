#pragma once

#include "Bindable/Bindable.h"
#include "Debug/ThrowMacros.h"

#include "Core/Vertex.h"

namespace dr
{
	namespace Bind
	{
		class VertexBuffer : public Bindable
		{
		public:
			VertexBuffer(Graphics& gfx, const dr::Dvtx::VertexBuffer& vbuf);

			void Bind(Graphics& gfx) noexcept override;
		protected:
			UINT stride;
			Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
		};
	}
}
