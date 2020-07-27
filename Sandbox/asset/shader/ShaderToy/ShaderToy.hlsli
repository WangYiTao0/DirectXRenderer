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