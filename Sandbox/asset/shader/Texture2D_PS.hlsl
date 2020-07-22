
struct PSIn
{
    float4 pos : SV_POSITION;
    float2 tc : Texcoord;
};

Texture2D tex : register(t3);
SamplerState splr : register(s0);



float4 main(PSIn psi) : SV_TARGET
{
    float4 sampleColor = tex.Sample(splr, psi.tc);
    return sampleColor;
}