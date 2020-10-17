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
// Tangent                  0   xyz         3     NONE   float   xyz 
// Bitangent                0   xyz         4     NONE   float   xyz 
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
// ShadowPosition           0   xyzw        5     NONE   float   xyzw
// SV_Position              0   xyzw        6      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[12], immediateIndexed
dcl_constantbuffer CB1[4], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_input v2.xy
dcl_input v3.xyz
dcl_input v4.xyz
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output o2.xyz
dcl_output o3.xyz
dcl_output o4.xy
dcl_output o5.xyzw
dcl_output_siv o6.xyzw, position
dcl_temps 2
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 o0.x, r0.xyzw, cb0[4].xyzw
dp4 o0.y, r0.xyzw, cb0[5].xyzw
dp4 o0.z, r0.xyzw, cb0[6].xyzw
dp3 o1.x, v1.xyzx, cb0[4].xyzx
dp3 o1.y, v1.xyzx, cb0[5].xyzx
dp3 o1.z, v1.xyzx, cb0[6].xyzx
dp3 o2.x, v3.xyzx, cb0[4].xyzx
dp3 o2.y, v3.xyzx, cb0[5].xyzx
dp3 o2.z, v3.xyzx, cb0[6].xyzx
dp3 o3.x, v4.xyzx, cb0[4].xyzx
dp3 o3.y, v4.xyzx, cb0[5].xyzx
dp3 o3.z, v4.xyzx, cb0[6].xyzx
mov o4.xy, v2.xyxx
dp4 r1.x, r0.xyzw, cb0[0].xyzw
dp4 r1.y, r0.xyzw, cb0[1].xyzw
dp4 r1.z, r0.xyzw, cb0[2].xyzw
dp4 r1.w, r0.xyzw, cb0[3].xyzw
dp4 o5.x, r1.xyzw, cb1[0].xyzw
dp4 o5.y, r1.xyzw, cb1[1].xyzw
dp4 o5.z, r1.xyzw, cb1[2].xyzw
dp4 o5.w, r1.xyzw, cb1[3].xyzw
dp4 o6.x, r0.xyzw, cb0[8].xyzw
dp4 o6.y, r0.xyzw, cb0[9].xyzw
dp4 o6.z, r0.xyzw, cb0[10].xyzw
dp4 o6.w, r0.xyzw, cb0[11].xyzw
ret 
// Approximately 28 instruction slots used
