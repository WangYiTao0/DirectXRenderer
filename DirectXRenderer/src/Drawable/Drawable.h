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
		void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);
		virtual void Update(float dt) noexcept = 0;
		void AddBind(std::unique_ptr<Bind::Bindable> bind) noexcept(!IS_DEBUG);
		void AddIndexBuffer(std::unique_ptr<Bind::IndexBuffer> ibuf) noexcept;
		virtual ~Drawable() = default;
	private:
		const Bind::IndexBuffer* pIndexBuffer = nullptr;
		std::vector<std::unique_ptr<Bind::Bindable>> binds;
	};
}