//#include "ShaderToy/2D_Clouds.hlsli"
//#include "ShaderToy/Elevated.hlsli"
#include "ShaderToy/Clouds.hlsli"


float4 main(float2 tc : Texcoord, float4 pos : SV_Position) : SV_TARGET
{
    float4 fragColor = { 0.0, 0.0, 0.0, 0.0 };
    
    float4 tempColor;
    // Time varying pixel color
    float3 col = 0.5 + 0.5 * cos(iTime + tc.xyx + float3(0, 2, 4));

    // Output to screen
    tempColor = iChannel0.Sample(splr, tc);

    fragColor = tempColor;
     
    Clouds(tempColor, tc);
    
    fragColor += tempColor;
    
    return fragColor;
}