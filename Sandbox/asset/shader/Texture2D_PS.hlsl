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

  /*  vec3 col = vec3(0.0, 0.0, 0.0);
    if (data.w < 0.0)
    {
        col = data.xyz;
    }
    else
    {
        // decompress velocity vector
        float ss = mod(data.w, 256.0) / 255.0;
        float st = floor(data.w / 256.0) / 255.0;

        // motion blur (linear blur across velocity vectors
        vec2 dir = (-1.0 + 2.0 * vec2(ss, st)) * 0.25;
        col = vec3(0.0, 0.0, 0.0);
        for (int i = 0; i < 32; i++)
        {
            float h = float(i) / 31.0;
            vec2 pos = tc + dir * h;
            //col += texture(iChannel1, pos).xyz;
            col += iChannel0.Sample(splr, pos).xyz;
        }
        col /= 32.0;
    }
    
    // vignetting	
    col *= 0.5 + 0.5 * pow(16.0 * tc.x * tc.y * (1.0 - tc.x) * (1.0 - tc.y), 0.1);

    col = clamp(col, 0.0, 1.0);
    col = col * 0.6 + 0.4 * col * col * (3.0 - 2.0 * col) + vec3(0.0, 0.0, 0.04);
   */
    fragColor = data;
     
    //Clouds(tempColor, tc);
    //fragColor = tempColor;
    
    return fragColor;
}