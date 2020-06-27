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
//   float specularIntensity;           // Offset:    0 Size:     4
//   float specularPower;               // Offset:    4 Size:     4
//   bool normalMapEnabled;             // Offset:    8 Size:     4
//   float padding;                     // Offset:   16 Size:     4 [unused]
//
// }
//
// cbuffer TransformCBuf
// {
//
//   float4x4 modelView;                // Offset:    0 Size:    64
//   float4x4 modelViewProj;            // Offset:   64 Size:    64 [unused]
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// splr                              sampler      NA          NA             s0      1 
// tex                               texture  float4          2d             t0      1 
// nmap                              texture  float4          2d             t2      1 
// PointLightCBuf                    cbuffer      NA          NA            cb0      1 
// ObjectCBuf                        cbuffer      NA          NA            cb1      1 
// TransformCBuf                     cbuffer      NA          NA            cb2      1 
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
dcl_constantbuffer CB1[1], immediateIndexed
dcl_constantbuffer CB2[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xy
dcl_output o0.xyzw
dcl_temps 4
if_nz cb1[0].z
  sample_indexable(texture2d)(float,float,float,float) r0.xyz, v2.xyxx, t2.xyzw, s0
  mad r0.xyz, r0.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), l(-1.000000, -1.000000, -1.000000, 0.000000)
  dp3 r1.x, r0.xyzx, cb2[0].xyzx
  dp3 r1.y, r0.xyzx, cb2[1].xyzx
  dp3 r1.z, r0.xyzx, cb2[2].xyzx
  dp3 r0.x, r1.xyzx, r1.xyzx
  rsq r0.x, r0.x
  mul r0.xyz, r0.xxxx, r1.xyzx
else 
  mov r0.xyz, v1.xyzx
endif 
add r1.xyz, -v0.xyzx, cb0[0].xyzx
dp3 r0.w, r1.xyzx, r1.xyzx
sqrt r1.w, r0.w
div r2.xyz, r1.xyzx, r1.wwww
mad r1.w, cb0[3].y, r1.w, cb0[3].x
mad r0.w, cb0[3].z, r0.w, r1.w
div r0.w, l(1.000000, 1.000000, 1.000000, 1.000000), r0.w
mul r3.xyz, cb0[2].wwww, cb0[2].xyzx
mul r3.xyz, r0.wwww, r3.xyzx
dp3 r1.w, r2.xyzx, r0.xyzx
max r1.w, r1.w, l(0.000000)
dp3 r2.x, r1.xyzx, r0.xyzx
mul r0.xyz, r0.xyzx, r2.xxxx
mad r0.xyz, r0.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), -r1.xyzx
dp3 r1.x, r0.xyzx, r0.xyzx
rsq r1.x, r1.x
mul r0.xyz, r0.xyzx, r1.xxxx
dp3 r1.x, v0.xyzx, v0.xyzx
rsq r1.x, r1.x
mul r1.xyz, r1.xxxx, v0.xyzx
mul r0.w, r0.w, cb1[0].x
dp3 r0.x, -r0.xyzx, r1.xyzx
max r0.x, r0.x, l(0.000000)
log r0.x, r0.x
mul r0.x, r0.x, cb1[0].y
exp r0.x, r0.x
mul r0.x, r0.x, r0.w
mad r0.yzw, r3.xxyz, r1.wwww, cb0[1].xxyz
sample_indexable(texture2d)(float,float,float,float) r1.xyz, v2.xyxx, t0.xyzw, s0
mad_sat o0.xyz, r0.yzwy, r1.xyzx, r0.xxxx
mov o0.w, l(1.000000)
ret 
// Approximately 44 instruction slots used