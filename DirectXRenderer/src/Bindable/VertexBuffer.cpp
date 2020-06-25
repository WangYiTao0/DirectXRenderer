#include "drpch.h"
#include "VertexBuffer.h"


namespace dr
{
	namespace Bind
	{
		void VertexBuffer::Bind(Graphics& gfx) noexcept
		{
			const UINT offset = 0u;
			GetContext(gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
		}
	}
}
