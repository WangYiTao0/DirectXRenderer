
struct PSIn
{
    float4 pos : SV_POSITION;
    float2 tc : Texcoord;
};

Texture2D tex : register(t3);
SamplerState splr : register(s0);

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * 0.5 * 400.0) / (400.0 + 0.5 - z * (400.0 - 0.5));
}

float4 main(PSIn psi) : SV_TARGET
{
    float depthvalue = tex.Sample(splr, psi.tc).r;
   
    float3 color = (LinearizeDepth(depthvalue) / 400.0);
    return float4(color, 1.0);
    //return float4(depthvalue, 1.0);
}