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
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output o2.xy
dcl_output_siv o3.xyzw, position
dcl_temps 1
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 o0.x, r0.xyzw, cb0[0].xyzw
dp4 o0.y, r0.xyzw, cb0[1].xyzw
dp4 o0.z, r0.xyzw, cb0[2].xyzw
dp3 o1.x, v1.xyzx, cb0[0].xyzx
dp3 o1.y, v1.xyzx, cb0[1].xyzx
dp3 o1.z, v1.xyzx, cb0[2].xyzx
mov o2.xy, v2.xyxx
dp4 o3.x, r0.xyzw, cb0[4].xyzw
dp4 o3.y, r0.xyzw, cb0[5].xyzw
dp4 o3.z, r0.xyzw, cb0[6].xyzw
dp4 o3.w, r0.xyzw, cb0[7].xyzw
ret 
// Approximately 14 instruction slots used
