cbuffer ShaderToy : register(b0)
{
	float3 iResolution; // viewport resolution (in pixels)
	float iTime; // shader playback time (in seconds)
    //float iTimeDelta; // render time (in seconds)
    // int iFrame; // shader playback frame
    //float iChannelTime[4]; // channel playback time (in seconds)
	float4 iMouse; // mouse pixel coords. xy: current (if MLB down), zw: click
    //float4 iDate; // (year, month, day, time in seconds)
}

Texture2D iChannel0 : register(t0);
Texture2D iChannel1 : register(t1);
Texture2D iChannel2 : register(t2);

SamplerState splr: register(s0); //linear repeat
SamplerState splr1 : register(s1); //linear clamp