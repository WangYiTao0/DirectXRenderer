#pragma once
#include "Base/FullscreenPass.h"
#include "Base/Sink.h"
#include "Base/Source.h"
#include "Bindable/BindableCommon.h"
#include "Core/Camera/Camera2D.h"

namespace dr
{
	class Graphics;
	namespace Rgph
	{
		class LightingPass : public FullscreenPass
		{
		public:
			LightingPass(std::string name, Graphics& gfx, unsigned int fullWidth, unsigned int fullHeight);

			void Execute(Graphics& gfx) const noxnd override;
			void Bind2DCamera(const Camera2D& cam);
		private:
			const Camera2D* p2DCamera = nullptr;
		};
	}
}

