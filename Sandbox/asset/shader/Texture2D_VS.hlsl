cbuffer Texture2DCbuf : register(b0)
{
    matrix model;
    matrix modelView;
    matrix modelViewProj;
};
    
struct VSIn
{
    float3 pos : Position;
    float2 tc : Texcoord;
};

struct VSOut
{
    float2 tc : Texcoord;
    float4 pos : SV_Position;
};

VSOut main(VSIn vsi)
{
    VSOut vso;
    float3 worldPos = (float3) mul(float4(vsi.pos, 1.0f), model);
    vso.tc = vsi.tc;
    vso.pos = mul(float4(vsi.pos, 1.0f), modelViewProj);
    
    return vso;
}