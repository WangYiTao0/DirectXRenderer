#include "Common/Transform.hlsli"
#include "Common/VShadow.hlsli"

struct VS_IN
{
    float3 pos : Position;
    float3 n : Normal;
    float2 tc : Texcoord;
};

struct VS_Out
{
    float3 worldPos : Position;
    float3 worldNormal : Normal;
    float2 tc : Texcoord;
    float4 pos : SV_Position;
};

VS_Out main(VS_IN vIn)
{
    VS_Out vso;
    vso.worldPos = (float3) mul(float4(vIn.pos, 1.0f), model);
    vso.worldNormal = mul(vIn.n, (float3x3) model);
    vso.tc = vIn.tc;
    vso.pos = mul(float4(vIn.pos, 1.0f), modelViewProj);
    return vso;
}   