//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer TransformCBuf
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
// TransformCBuf                     cbuffer      NA          NA            cb0      1 
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
// Position                 0   xyz         0     NONE   float   xyz 
// Normal                   0   xyz         1     NONE   float   xyz 
// Texcoord                 0   xy          2     NONE   float   xy  
// SV_Position              0   xyzw        3      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output o2.xy
dcl_output_siv o3.xyzw, position
dcl_temps 4
//
// Initial variable locations:
//   v0.x <- pos.x; v0.y <- pos.y; v0.z <- pos.z; 
//   v1.x <- n.x; v1.y <- n.y; v1.z <- n.z; 
//   v2.x <- tc.x; v2.y <- tc.y; 
//   o3.x <- <main return value>.pos.x; o3.y <- <main return value>.pos.y; o3.z <- <main return value>.pos.z; o3.w <- <main return value>.pos.w; 
//   o2.x <- <main return value>.tc.x; o2.y <- <main return value>.tc.y; 
//   o1.x <- <main return value>.viewNormal.x; o1.y <- <main return value>.viewNormal.y; o1.z <- <main return value>.viewNormal.z; 
//   o0.x <- <main return value>.viewPos.x; o0.y <- <main return value>.viewPos.y; o0.z <- <main return value>.viewPos.z
//
#line 14 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongDif_VS.hlsl"
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 r1.x, r0.xyzw, cb0[0].xyzw  // r1.x <- vso.viewPos.x
dp4 r1.y, r0.xyzw, cb0[1].xyzw  // r1.y <- vso.viewPos.y
dp4 r1.z, r0.xyzw, cb0[2].xyzw  // r1.z <- vso.viewPos.z

#line 15
dp3 r2.x, v1.xyzx, cb0[0].xyzx  // r2.x <- vso.viewNormal.x
dp3 r2.y, v1.xyzx, cb0[1].xyzx  // r2.y <- vso.viewNormal.y
dp3 r2.z, v1.xyzx, cb0[2].xyzx  // r2.z <- vso.viewNormal.z

#line 16
dp4 r3.x, r0.xyzw, cb0[4].xyzw  // r3.x <- vso.pos.x
dp4 r3.y, r0.xyzw, cb0[5].xyzw  // r3.y <- vso.pos.y
dp4 r3.z, r0.xyzw, cb0[6].xyzw  // r3.z <- vso.pos.z
dp4 r3.w, r0.xyzw, cb0[7].xyzw  // r3.w <- vso.pos.w

#line 17
mov r0.xy, v2.xyxx  // r0.x <- vso.tc.x; r0.y <- vso.tc.y

#line 18
mov o3.xyzw, r3.xyzw
mov o0.xyz, r1.xyzx
mov o1.xyz, r2.xyzx
mov o2.xy, r0.xyxx
ret 
// Approximately 18 instruction slots used
