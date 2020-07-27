

struct PS_IN
{
    float3 worldPos : Position;
    float3 worldNormal : Normal;
    float2 tc : Texcoord;
};

struct PS_OUT
{
    float4 color : SV_Target0;
    float4 pos : SV_Target1;
    float4 normal : SV_Target2;
    //float4 tc : SV_Target3;
};

Texture2D tex : register(t0);
Texture2D spec : register(t1);
Texture2D nmap : register(t2);
SamplerState splr : register(s0);

PS_OUT main(PS_IN pIn) : SV_TARGET
{
    PS_OUT pout;
    
    pout.color.rgb = tex.Sample(splr, pIn.tc).rgb;
    pout.color.r = spec.Sample(splr, pIn.tc).a;
    pout.pos = float4(pIn.worldPos, 1.0);
    //pout.normal = float4(pIn.worldNormal, 1.0);
    pout.normal = nmap.Sample(splr, pIn.tc);
    
    //pout.tc = pIn.tc;

    return pout;
}