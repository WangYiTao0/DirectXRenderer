#include "Common/ShaderOps.hlsli"
#include "Common/LightVectorData.hlsli"

#include "Common/PointLight.hlsli"

cbuffer ObjectCBuf : register(b1)
{
    float3 specularColor;
    float specularWeight;
    float specularGloss;
};

Texture2D color : register(t0);
Texture2D position : register(t1);
Texture2D normal : register(t2);

sampler splr : register(s0);

float4 main(float2 tc : Texcoord):SV_Target0
{
    float3 diffuse = color.Sample(splr, tc);
    float3 pos = position.Sample(splr, tc);
    float3 nor = normal.Sample(splr, tc);
    float3 specular;
    float3 lightdiffuse;
    
    //light Calculate
    
    // renormalize interpolated normal
    nor = normalize(nor);
	// fragment to light vector data
    const LightVectorData lv = CalculateLightVectorData(viewLightPos, pos);
	// attenuation
    const float att = Attenuate(attConst, attLin, attQuad, lv.distToL);
	// diffuse
    lightdiffuse = Diffuse(diffuseColor, diffuseIntensity, att, lv.dirToL, nor);
	// specular
    specular = Speculate(diffuseColor * diffuseIntensity * specularColor, specularWeight, nor, lv.vToL, pos, att, specularGloss);
    
    //final color
    float4 lighting = float4(saturate((lightdiffuse + ambient) * diffuse + specular), 1.0f);
    return lighting;

}