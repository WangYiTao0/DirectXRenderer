#pragma once
#include "TransformCbuf.h"
#include "Core/DynamicConstant.h"

namespace dr
{
	namespace Bind
	{
		class TransformCbufScaling : public TransformCbuf
		{
		public:
			TransformCbufScaling(Graphics& gfx, float scale);
			void Accept(TechniqueProbe& probe) override;
			void Bind(Graphics& gfx) noxnd override;
			std::unique_ptr<CloningBindable> Clone() const noexcept override;
		private:
			static Dcb::RawLayout MakeLayout();
		private:
			Dcb::Buffer buf;
		};
	}
}