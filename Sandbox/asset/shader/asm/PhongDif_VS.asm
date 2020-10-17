//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer TransformCBuf
// {
//
//   float4x4 model;                    // Offset:    0 Size:    64
//   float4x4 modelView;                // Offset:   64 Size:    64
//   float4x4 modelViewProj;            // Offset:  128 Size:    64
//
// }
//
// cbuffer ShadowTransformCBuf
// {
//
//   float4x4 shadowPos;                // Offset:    0 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// TransformCBuf                     cbuffer      NA          NA            cb0      1 
// ShadowTransformCBuf               cbuffer      NA          NA            cb1      1 
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
// ShadowPosition           0   xyzw        3     NONE   float   xyzw
// SV_Position              0   xyzw        4      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[12], immediateIndexed
dcl_constantbuffer CB1[4], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output o2.xy
dcl_output o3.xyzw
dcl_output_siv o4.xyzw, position
dcl_temps 2
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 o0.x, r0.xyzw, cb0[4].xyzw
dp4 o0.y, r0.xyzw, cb0[5].xyzw
dp4 o0.z, r0.xyzw, cb0[6].xyzw
dp3 o1.x, v1.xyzx, cb0[4].xyzx
dp3 o1.y, v1.xyzx, cb0[5].xyzx
dp3 o1.z, v1.xyzx, cb0[6].xyzx
mov o2.xy, v2.xyxx
dp4 r1.x, r0.xyzw, cb0[0].xyzw
dp4 r1.y, r0.xyzw, cb0[1].xyzw
dp4 r1.z, r0.xyzw, cb0[2].xyzw
dp4 r1.w, r0.xyzw, cb0[3].xyzw
dp4 o3.x, r1.xyzw, cb1[0].xyzw
dp4 o3.y, r1.xyzw, cb1[1].xyzw
dp4 o3.z, r1.xyzw, cb1[2].xyzw
dp4 o3.w, r1.xyzw, cb1[3].xyzw
dp4 o4.x, r0.xyzw, cb0[8].xyzw
dp4 o4.y, r0.xyzw, cb0[9].xyzw
dp4 o4.z, r0.xyzw, cb0[10].xyzw
dp4 o4.w, r0.xyzw, cb0[11].xyzw
ret 
// Approximately 22 instruction slots used