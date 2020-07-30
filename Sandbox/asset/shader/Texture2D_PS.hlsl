//#include "ShaderToy/2D_Clouds.hlsli"
#include "ShaderToy/Elevated.hlsli"
//#include "ShaderToy/Clouds.hlsli"


float4 main(float2 tc : Texcoord, float4 pos : SV_Position) : SV_TARGET
{
    float4 fragColor = { 0.0, 0.0, 0.0, 0.0 };
    
    float4 tempColor;

    tc.y = -tc.y;
    // Output to screen
    //tempColor = iChannel0.Sample(splr, tc);
    //fragColor = tempColor;
    
    //vec4 data = texture(iChannel1, uv);
    vec4 data = iChannel0.Sample(splr, tc);
    
    vec4 data1 = iChannel4.Sample(splr, tc);
    
    //vec4 final = lerp(data, data1, 0.5);

    
    fragColor = data;
  

     
    //Clouds(tempColor, tc);
    //fragColor = tempColor;
    
    return fragColor;
}