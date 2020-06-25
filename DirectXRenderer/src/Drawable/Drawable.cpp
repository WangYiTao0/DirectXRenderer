#include "drpch.h"
#include "Drawable.h"
#include "Debug/ThrowMacros.h"
#include "Bindable/IndexBuffer.h"
#include <cassert>
#include <typeinfo>

namespace dr
{
	void Drawable::Draw(Graphics& gfx) const noexcept(!IS_DEBUG)
	{
		for (auto& b : binds)
		{
			b->Bind(gfx);
		}
		gfx.DrawIndexed(pIndexBuffer->GetCount());
	}

	void Drawable::AddBind(std::unique_ptr<Bind::Bindable> bind) noexcept(!IS_DEBUG)
	{
		assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind) != typeid(Bind::IndexBuffer));
		binds.push_back(std::move(bind));
	}

	void Drawable::AddIndexBuffer(std::unique_ptr<Bind::IndexBuffer> ibuf) noexcept
	{
		assert("Attempting to add index buffer a second time" && pIndexBuffer == nullptr);
		pIndexBuffer = ibuf.get();
		binds.push_back(std::move(ibuf));
	}
}
