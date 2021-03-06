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
//   bool useGlossAlpha;                // Offset:    0 Size:     4
//   bool useSpecularMap;               // Offset:    4 Size:     4
//   float3 specularColor;              // Offset:   16 Size:    12
//   float specularWeight;              // Offset:   28 Size:     4
//   float specularGloss;               // Offset:   32 Size:     4
//   bool useNormalMap;                 // Offset:   36 Size:     4
//   float normalMapWeight;             // Offset:   40 Size:     4
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
// spec                              texture  float4          2d             t1      1 
// nmap                              texture  float4          2d             t2      1 
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
// Tangent                  0   xyz         2     NONE   float   xyz 
// Bitangent                0   xyz         3     NONE   float   xyz 
// Texcoord                 0   xy          4     NONE   float   xy  
// ShadowPosition           0   xyzw        5     NONE   float   xyz 
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
dcl_constantbuffer CB1[3], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_comparison
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_resource_texturecube (float,float,float,float) t3
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xyz
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xy
dcl_input_ps linear v5.xyz
dcl_output o0.xyzw
dcl_temps 7
sample_indexable(texture2d)(float,float,float,float) r0.xyzw, v4.xyxx, t0.xyzw, s0
lt r0.w, r0.w, l(0.100000)
discard_nz r0.w
dp3 r0.w, v5.xyzx, v5.xyzx
rsq r1.x, r0.w
mul r1.xyz, r1.xxxx, v5.xyzx
sqrt r0.w, r0.w
mul r0.w, r0.w, l(0.010000)
sample_c_lz_indexable(texturecube)(float,float,float,float) r0.w, r1.xyzx, t3.xxxx, s1, r0.w
ne r1.x, r0.w, l(0.000000)
if_nz r1.x
  dp3 r1.x, v1.xyzx, v0.xyzx
  ge r1.x, r1.x, l(0.000000)
  movc r1.xyz, r1.xxxx, -v1.xyzx, v1.xyzx
  dp3 r1.w, r1.xyzx, r1.xyzx
  rsq r1.w, r1.w
  mul r1.xyz, r1.wwww, r1.xyzx
  if_nz cb1[2].y
    dp3 r1.w, v2.xyzx, v2.xyzx
    rsq r1.w, r1.w
    mul r2.xyz, r1.wwww, v2.xyzx
    dp3 r1.w, v3.xyzx, v3.xyzx
    rsq r1.w, r1.w
    mul r3.xyz, r1.wwww, v3.xyzx
    sample_indexable(texture2d)(float,float,float,float) r4.xyz, v4.xyxx, t2.xyzw, s0
    mad r4.xyz, r4.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), l(-1.000000, -1.000000, -1.000000, 0.000000)
    mul r3.xyz, r3.xyzx, r4.yyyy
    mad r2.xyz, r4.xxxx, r2.xyzx, r3.xyzx
    mad r2.xyz, r4.zzzz, r1.xyzx, r2.xyzx
    dp3 r1.w, r2.xyzx, r2.xyzx
    rsq r1.w, r1.w
    mad r2.xyz, r2.xyzx, r1.wwww, -r1.xyzx
    mad r1.xyz, cb1[2].zzzz, r2.xyzx, r1.xyzx
  endif 
  add r2.xyz, -v0.xyzx, cb0[0].xyzx
  dp3 r1.w, r2.xyzx, r2.xyzx
  sqrt r2.w, r1.w
  div r3.xyz, r2.xyzx, r2.wwww
  sample_indexable(texture2d)(float,float,float,float) r4.xyzw, v4.xyxx, t1.xyzw, s0
  movc r4.xyz, cb1[0].yyyy, r4.xyzx, cb1[1].xyzx
  mul r3.w, r4.w, l(13.000000)
  exp r3.w, r3.w
  movc r3.w, cb1[0].x, r3.w, cb1[2].x
  mad r2.w, cb0[3].y, r2.w, cb0[3].x
  mad r1.w, cb0[3].z, r1.w, r2.w
  div r1.w, l(1.000000, 1.000000, 1.000000, 1.000000), r1.w
  mul r5.xyz, cb0[2].wwww, cb0[2].xyzx
  mul r6.xyz, r1.wwww, r5.xyzx
  dp3 r2.w, r3.xyzx, r1.xyzx
  max r2.w, r2.w, l(0.000000)
  mul r3.xyz, r2.wwww, r6.xyzx
  mul r4.xyz, r4.xyzx, r5.xyzx
  dp3 r2.w, r2.xyzx, r1.xyzx
  mul r1.xyz, r1.xyzx, r2.wwww
  mad r1.xyz, r1.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000), -r2.xyzx
  dp3 r2.x, r1.xyzx, r1.xyzx
  rsq r2.x, r2.x
  mul r1.xyz, r1.xyzx, r2.xxxx
  dp3 r2.x, v0.xyzx, v0.xyzx
  rsq r2.x, r2.x
  mul r2.xyz, r2.xxxx, v0.xyzx
  mul r4.xyz, r1.wwww, r4.xyzx
  mul r4.xyz, r4.xyzx, cb1[1].wwww
  dp3 r1.x, -r1.xyzx, r2.xyzx
  max r1.x, r1.x, l(0.000000)
  log r1.x, r1.x
  mul r1.x, r1.x, r3.w
  exp r1.x, r1.x
  mul r1.xyz, r1.xxxx, r4.xyzx
  mul r2.xyz, r0.wwww, r3.xyzx
  mul r1.xyz, r0.wwww, r1.xyzx
else 
  mov r2.xyz, l(0,0,0,0)
  mov r1.xyz, l(0,0,0,0)
endif 
add r2.xyz, r2.xyzx, cb0[1].xyzx
mad_sat o0.xyz, r2.xyzx, r0.xyzx, r1.xyzx
mov o0.w, l(1.000000)
ret 
// Approximately 79 instruction slots used
