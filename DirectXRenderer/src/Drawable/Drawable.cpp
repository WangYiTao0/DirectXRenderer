#include "drpch.h"
#include "Drawable.h"
#include "Debug/ThrowMacros.h"
#include "Bindable/IndexBuffer.h"
#include <cassert>
#include <typeinfo>

namespace dr
{
	void Drawable::Draw(Graphics& gfx) const noxnd
	{
		for (auto& b : binds)
		{
			b->Bind(gfx);
		}
		gfx.DrawIndexed(pIndexBuffer->GetCount());
	}

	void Drawable::AddBind(std::shared_ptr<Bind::Bindable> bind) noxnd
	{
		// special case for index buffer
		if (typeid(*bind) == typeid(Bind::IndexBuffer))
		{
			assert("Binding multiple index buffers not allowed" && pIndexBuffer == nullptr);
			pIndexBuffer = &static_cast<Bind::IndexBuffer&>(*bind);
		}
		binds.push_back(std::move(bind));
	}
}

