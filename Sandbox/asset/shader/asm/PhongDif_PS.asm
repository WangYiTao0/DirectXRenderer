//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer PointLightCBuf
// {
//
//   float3 viewLightPos;               // Offset:    0 Size:    12
//   float3 ambient;                    // Offset:   16 Size:    12
//   float3 diffuseColor;               // Offset:   32 Size:    12
//   float diffuseIntensity;            // Offset:   44 Size:     4
//   float attConst;                    // Offset:   48 Size:     4
//   float attLin;                      // Offset:   52 Size:     4
//   float attQuad;                     // Offset:   56 Size:     4
//
// }
//
// cbuffer ObjectCBuf
// {
//
//   float3 specularColor;              // Offset:    0 Size:    12
//   float specularWeight;              // Offset:   12 Size:     4
//   float specularGloss;               // Offset:   16 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// splr                              sampler      NA          NA             s0      1 
// ssam                            sampler_c      NA          NA             s1      1 
// tex                               texture  float4          2d             t0      1 
// smap                              texture  float4        cube             t3      1 
// PointLightCBuf                    cbuffer      NA          NA            cb0      1 
// ObjectCBuf                        cbuffer      NA          NA            cb1      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
// Normal                   0   xyz         1     NONE   float   xyz 
// Texcoord                 0   xy          2     NONE   float   xy  
// ShadowPosition           0   xyzw        3     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[4], immediateIndexed
dcl_constantbuffer CB1[2], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_comparison
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texturecube (float,float,float,float) t3
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xy
dcl_input_ps linear v3.xyz
dcl_output o0.xyzw
dcl_temps 4
dp3 r0.x, v0.xyzx, v0.xyzx
rsq r0.x, r0.x
mul r0.xyz, r0.xxxx, v0.xyzx
dp3 r0.w, v1.xyzx, v1.xyzx
rsq r0.w, r0.w
mul r1.xyz, r0.wwww, v1.xyzx
add r2.xyz, -v0.xyzx, cb0[0].xyzx
dp3 r0.w, r2.xyzx, r1.xyzx
mul r3.xyz, r0.wwww, r1.xyzx
mad r3.xyz, r3.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), -r2.xyzx
dp3 r0.w, r3.xyzx, r3.xyzx
rsq r0.w, r0.w
mul r3.xyz, r0.wwww, r3.xyzx
dp3 r0.x, -r3.xyzx, r0.xyzx
max r0.x, r0.x, l(0.000000)
log r0.x, r0.x
mul r0.x, r0.x, cb1[1].x
exp r0.x, r0.x
dp3 r0.y, r2.xyzx, r2.xyzx
sqrt r0.z, r0.y
mad r0.w, cb0[3].y, r0.z, cb0[3].x
div r2.xyz, r2.xyzx, r0.zzzz
dp3 r0.z, r2.xyzx, r1.xyzx
max r0.z, r0.z, l(0.000000)
mad r0.y, cb0[3].z, r0.y, r0.w
div r0.y, l(1.000000, 1.000000, 1.000000, 1.000000), r0.y
mul r1.xyz, cb0[2].wwww, cb0[2].xyzx
mul r2.xyz, r1.xyzx, cb1[0].xyzx
mul r1.xyz, r0.yyyy, r1.xyzx
mul r2.xyz, r0.yyyy, r2.xyzx
mul r2.xyz, r2.xyzx, cb1[0].wwww
mul r0.xyw, r0.xxxx, r2.xyxz
mul r1.xyz, r0.zzzz, r1.xyzx
dp3 r0.z, v3.xyzx, v3.xyzx
rsq r1.w, r0.z
sqrt r0.z, r0.z
mul r0.z, r0.z, l(0.010000)
mul r2.xyz, r1.wwww, v3.xyzx
sample_c_lz_indexable(texturecube)(float,float,float,float) r0.z, r2.xyzx, t3.xxxx, s1, r0.z
mul r0.xyw, r0.zzzz, r0.xyxw
ne r1.w, r0.z, l(0.000000)
mul r1.xyz, r0.zzzz, r1.xyzx
and r1.xyz, r1.xyzx, r1.wwww
and r0.xyz, r0.xywx, r1.wwww
add r1.xyz, r1.xyzx, cb0[1].xyzx
sample_indexable(texture2d)(float,float,float,float) r2.xyz, v2.xyxx, t0.xyzw, s0
mad_sat o0.xyz, r1.xyzx, r2.xyzx, r0.xyzx
mov o0.w, l(1.000000)
ret 
// Approximately 49 instruction slots used
