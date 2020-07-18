#include "Drawable.h"
namespace dr
{
	class Tex2D : public Drawable
	{
	public:
		Tex2D(Graphics& gfx, std::string path, float width, float height);
		//Tex2D(Graphics& gfx, std::string path, float width, float height);
		void SetPos(DirectX::XMFLOAT3 pos) noexcept;
		void SetRotation(float roll, float pitch, float yaw) noexcept;
		DirectX::XMMATRIX GetTransformXM() const noexcept override;
		void SpawnControlWindow(Graphics& gfx, const std::string& name) noexcept;
	private:
		DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
	};
}
