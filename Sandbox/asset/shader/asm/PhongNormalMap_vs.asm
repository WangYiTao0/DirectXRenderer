//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer CBuf
// {
//
//   float4x4 modelView;                // Offset:    0 Size:    64
//   float4x4 modelViewProj;            // Offset:   64 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// CBuf                              cbuffer      NA          NA            cb0      1 
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
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
// Normal                   0   xyz         1     NONE   float   xyz 
// Tangent                  0   xyz         2     NONE   float   xyz 
// Bitangent                0   xyz         3     NONE   float   xyz 
// Texcoord                 0   xy          4     NONE   float   xy  
// SV_Position              0   xyzw        5      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xyz
dcl_input v3.xyz
dcl_input v4.xy
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output o2.xyz
dcl_output o3.xyz
dcl_output o4.xy
dcl_output_siv o5.xyzw, position
dcl_temps 6
//
// Initial variable locations:
//   v0.x <- pos.x; v0.y <- pos.y; v0.z <- pos.z; 
//   v1.x <- n.x; v1.y <- n.y; v1.z <- n.z; 
//   v2.x <- tan.x; v2.y <- tan.y; v2.z <- tan.z; 
//   v3.x <- bitan.x; v3.y <- bitan.y; v3.z <- bitan.z; 
//   v4.x <- tc.x; v4.y <- tc.y; 
//   o5.x <- <main return value>.pos.x; o5.y <- <main return value>.pos.y; o5.z <- <main return value>.pos.z; o5.w <- <main return value>.pos.w; 
//   o4.x <- <main return value>.tc.x; o4.y <- <main return value>.tc.y; 
//   o3.x <- <main return value>.bitan.x; o3.y <- <main return value>.bitan.y; o3.z <- <main return value>.bitan.z; 
//   o2.x <- <main return value>.tan.x; o2.y <- <main return value>.tan.y; o2.z <- <main return value>.tan.z; 
//   o1.x <- <main return value>.normal.x; o1.y <- <main return value>.normal.y; o1.z <- <main return value>.normal.z; 
//   o0.x <- <main return value>.viewPos.x; o0.y <- <main return value>.viewPos.y; o0.z <- <main return value>.viewPos.z
//
#line 20 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongNormalMap_vs.hlsl"
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 r1.x, r0.xyzw, cb0[0].xyzw  // r1.x <- vso.viewPos.x
dp4 r1.y, r0.xyzw, cb0[1].xyzw  // r1.y <- vso.viewPos.y
dp4 r1.z, r0.xyzw, cb0[2].xyzw  // r1.z <- vso.viewPos.z

#line 21
dp3 r2.x, v1.xyzx, cb0[0].xyzx  // r2.x <- vso.normal.x
dp3 r2.y, v1.xyzx, cb0[1].xyzx  // r2.y <- vso.normal.y
dp3 r2.z, v1.xyzx, cb0[2].xyzx  // r2.z <- vso.normal.z

#line 22
dp3 r3.x, v2.xyzx, cb0[0].xyzx  // r3.x <- vso.tan.x
dp3 r3.y, v2.xyzx, cb0[1].xyzx  // r3.y <- vso.tan.y
dp3 r3.z, v2.xyzx, cb0[2].xyzx  // r3.z <- vso.tan.z

#line 23
dp3 r4.x, v3.xyzx, cb0[0].xyzx  // r4.x <- vso.bitan.x
dp3 r4.y, v3.xyzx, cb0[1].xyzx  // r4.y <- vso.bitan.y
dp3 r4.z, v3.xyzx, cb0[2].xyzx  // r4.z <- vso.bitan.z

#line 24
dp4 r5.x, r0.xyzw, cb0[4].xyzw  // r5.x <- vso.pos.x
dp4 r5.y, r0.xyzw, cb0[5].xyzw  // r5.y <- vso.pos.y
dp4 r5.z, r0.xyzw, cb0[6].xyzw  // r5.z <- vso.pos.z
dp4 r5.w, r0.xyzw, cb0[7].xyzw  // r5.w <- vso.pos.w

#line 25
mov r0.xy, v4.xyxx  // r0.x <- vso.tc.x; r0.y <- vso.tc.y

#line 26
mov o5.xyzw, r5.xyzw
mov o0.xyz, r1.xyzx
mov o1.xyz, r2.xyzx
mov o2.xyz, r3.xyzx
mov o3.xyz, r4.xyzx
mov o4.xy, r0.xyxx
ret 
// Approximately 26 instruction slots used
