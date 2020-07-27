
#include "ShaderToy/ShaderToy.hlsli"

struct PSIn
{
    float4 pos : SV_POSITION;
    float2 tc : Texcoord;
};


Texture2D tex : register(t0);
SamplerState splr : register(s0);


float4 main(PSIn psi) : SV_TARGET
{
    // Time varying pixel color
    float3 col = 0.5 + 0.5 * cos(iTime + psi.tc.xyx + float3(0, 2, 4));

    // Output to screen
    float4 fragColor = float4(col, 1.0);
    
    return fragColor;
}