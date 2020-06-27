#pragma once
#include <myRenderer.h>
#include <string>
#include <DirectXMath.h>


class TexturePreprocessor
{
public:
	static void FlipYAllNormalMapsInObj(const std::string& objPath);
	static void FlipYNormalMap(const std::string& pathIn, const std::string& pathOut);
	static void ValidateNormalMap(const std::string& pathIn, float thresholdMin, float thresholdMax);
	static void MakeStripes(const std::string& pathOut, int size, int stripeWidth);
private:
	template<typename F>
	static void TransformFile(const std::string& pathIn, const std::string& pathOut, F&& func);
	template<typename F>
	static void TransformSurface(dr::Surface& surf, F&& func);
	static DirectX::XMVECTOR ColorToVector(dr::Surface::Color c) noexcept;
	static dr::Surface::Color VectorToColor(DirectX::FXMVECTOR n) noexcept;
};

