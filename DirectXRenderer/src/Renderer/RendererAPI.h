#include "drpch.h"

namespace dr
{
	using RendererID = uint32_t;

	enum class RendererAPIType
	{
		None = 0,
		OpenGL,
		Vulkan,
		DirectX11,
		DirectX12
	};

	enum class PrimitiveType
	{
		None = 0, Triangles, Lines
	};
}