Texture2D tex : register(t5);
SamplerState splr;

float4 main(float2 uv : Texcoord) : SV_Target
{
	return  tex.Sample(splr, uv).rgba;
}
