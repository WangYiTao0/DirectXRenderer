#pragma once
#include "Core/Graphics.h"
#include "SolidSphere.h"
#include "Bindable/ConstantBuffers.h"
#include "Debug/ConditionalNoexcept.h"

namespace dr
{
	class Camera3D;

	namespace Rgph
	{
		class RenderGraph;
	}
	class PointLight
	{
	public:
		PointLight(Graphics& gfx, float radius = 0.5f);
		void SpawnControlWindow() noexcept;
		void Reset() noexcept;
		void Submit() const noxnd;
		void Bind(Graphics& gfx, DirectX::FXMMATRIX view) const noexcept;
		void LinkTechniques(Rgph::RenderGraph&);
		std::shared_ptr<Camera3D> ShareCamera() const noexcept;
	private:
		struct PointLightCBuf
		{
			alignas(16) DirectX::XMFLOAT3 pos;
			alignas(16) DirectX::XMFLOAT3 ambient;
			alignas(16) DirectX::XMFLOAT3 diffuseColor;
			float diffuseIntensity;
			float attConst;
			float attLin;
			float attQuad;
		};
	private:
		PointLightCBuf cbData;
		mutable SolidSphere mesh;
		mutable Bind::PixelConstantBuffer<PointLightCBuf> cbuf;
		std::shared_ptr<Camera3D> pCamera;
	};
}