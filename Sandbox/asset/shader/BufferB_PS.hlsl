
//#include "ShaderToy/Oceanic.hlsli"
#include "ShaderToy/Seascape.hlsli"
float4 main(float2 tc : Texcoord, float4 pos : SV_Position) : SV_TARGET
{
    float3 col = 0.5 + 0.5 * cos(iTime + tc.xyx + float3(0, 2, 4));

    float4 fragColor = float4(col, 1.0);
    Seascape(fragColor, tc);
    return fragColor;
}