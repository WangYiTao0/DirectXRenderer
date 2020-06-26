#include "drpch.h"
#include "Bindable.h"


namespace dr
{
	namespace Bind
	{
		ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
		{
			return gfx.m_pContext.Get();
		}

		ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
		{
			return gfx.m_pDevice.Get();
		}

		DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(IS_DEBUG)
		{
#ifndef NDEBUG
			return gfx.infoManager;
#else
			throw std::logic_error("YouFuckedUp! (tried to access gfx.infoManager in Release config)");
#endif
		}
	}
}
