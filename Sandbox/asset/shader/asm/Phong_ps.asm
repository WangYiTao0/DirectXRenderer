//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer LightCBuf
// {
//
//   float3 lightPos;                   // Offset:    0 Size:    12
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
//   float padding[2];                  // Offset:   16 Size:    20 [unused]
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
// LightCBuf                         cbuffer      NA          NA            cb0      1 
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
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[4], immediateIndexed
dcl_constantbuffer CB1[1], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xy
dcl_output o0.xyzw
dcl_temps 4
//
// Initial variable locations:
//   v0.x <- worldPos.x; v0.y <- worldPos.y; v0.z <- worldPos.z; 
//   v1.x <- n.x; v1.y <- n.y; v1.z <- n.z; 
//   v2.x <- tc.x; v2.y <- tc.y; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 27 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_ps.hlsl"
mov r0.xyz, -v0.xyzx
add r0.xyz, r0.xyzx, cb0[0].xyzx  // r0.x <- vToL.x; r0.y <- vToL.y; r0.z <- vToL.z

#line 28
dp3 r0.w, r0.xyzx, r0.xyzx
sqrt r0.w, r0.w  // r0.w <- distToL

#line 29
div r1.xyz, r0.xyzx, r0.wwww  // r1.x <- dirToL.x; r1.y <- dirToL.y; r1.z <- dirToL.z

#line 31
mul r1.w, r0.w, cb0[3].y
add r1.w, r1.w, cb0[3].x
mul r0.w, r0.w, r0.w
mul r0.w, r0.w, cb0[3].z
add r0.w, r0.w, r1.w
div r0.w, l(1.000000), r0.w  // r0.w <- att

#line 33
mul r2.xyz, cb0[2].wwww, cb0[2].xyzx
mul r2.xyz, r0.wwww, r2.xyzx
dp3 r1.x, r1.xyzx, v1.xyzx
max r1.x, r1.x, l(0.000000)
mul r1.xyz, r1.xxxx, r2.xyzx  // r1.x <- diffuse.x; r1.y <- diffuse.y; r1.z <- diffuse.z

#line 35
dp3 r1.w, r0.xyzx, v1.xyzx
mul r2.xyz, r1.wwww, v1.xyzx  // r2.x <- w.x; r2.y <- w.y; r2.z <- w.z

#line 36
mul r2.xyz, r2.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000)
mov r0.xyz, -r0.xyzx
add r0.xyz, r0.xyzx, r2.xyzx  // r0.x <- r.x; r0.y <- r.y; r0.z <- r.z

#line 38
mul r2.xyz, cb0[2].wwww, cb0[2].xyzx
mul r2.xyz, r0.wwww, r2.xyzx
mul r2.xyz, r2.xyzx, cb1[0].xxxx
mov r0.xyz, -r0.xyzx
dp3 r0.w, r0.xyzx, r0.xyzx
rsq r0.w, r0.w
mul r0.xyz, r0.wwww, r0.xyzx
dp3 r0.w, v0.xyzx, v0.xyzx
rsq r0.w, r0.w
mul r3.xyz, r0.wwww, v0.xyzx
dp3 r0.x, r0.xyzx, r3.xyzx
max r0.x, r0.x, l(0.000000)
log r0.x, r0.x
mul r0.x, r0.x, cb1[0].y
exp r0.x, r0.x
mul r0.xyz, r0.xxxx, r2.xyzx  // r0.x <- specular.x; r0.y <- specular.y; r0.z <- specular.z

#line 40
add r1.xyz, r1.xyzx, cb0[1].xyzx
add r0.xyz, r0.xyzx, r1.xyzx
max r0.xyz, r0.xyzx, l(0.000000, 0.000000, 0.000000, 0.000000)
min r0.xyz, r0.xyzx, l(1.000000, 1.000000, 1.000000, 0.000000)
sample_indexable(texture2d)(float,float,float,float) r1.xyzw, v2.xyxx, t0.xyzw, s0
mov r0.w, l(1.000000)
mul o0.xyzw, r0.xyzw, r1.xyzw
ret 
// Approximately 45 instruction slots used
