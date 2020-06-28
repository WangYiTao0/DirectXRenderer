#include "drpch.h"
#include "GraphicsResource.h"
#include <stdexcept>

namespace dr
{
	ID3D11DeviceContext* GraphicsResource::GetContext(Graphics& gfx) noexcept
	{
		return gfx.m_pContext.Get();
	}

	ID3D11Device* GraphicsResource::GetDevice(Graphics& gfx) noexcept
	{
		return gfx.m_pDevice.Get();
	}

	DxgiInfoManager& GraphicsResource::GetInfoManager(Graphics& gfx)
	{
#ifndef NDEBUG
		return gfx.infoManager;
#else
		throw std::logic_error("YouFuckedUp! (tried to access gfx.infoManager in Release config)");
#endif
	}
}