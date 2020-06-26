#pragma once
#include "Core/Graphics.h"
#include <DirectXMath.h>
namespace dr
{
	namespace Bind
	{
		class Bindable;
		class IndexBuffer;
	}

	class Drawable
	{
	public:
		Drawable() = default;
		Drawable(const Drawable&) = delete;
		virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
		void Draw(Graphics& gfx) const noxnd;
		virtual void Update(float dt) noexcept {};
		virtual ~Drawable() = default;

		void AddBind(std::shared_ptr<Bind::Bindable> bind) noxnd;	
	private:
		const Bind::IndexBuffer* pIndexBuffer = nullptr;
		std::vector<std::shared_ptr<Bind::Bindable>> binds;
	};
}