//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer TransformCBuf
// {
//
//   float4x4 model;                    // Offset:    0 Size:    64 [unused]
//   float4x4 modelView;                // Offset:   64 Size:    64 [unused]
//   float4x4 modelViewProj;            // Offset:  128 Size:    64
//
// }
//
// cbuffer Offset
// {
//
//   float offset;                      // Offset:    0 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// TransformCBuf                     cbuffer      NA          NA            cb0      1 
// Offset                            cbuffer      NA          NA            cb1      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
// Normal                   0   xyz         1     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_constantbuffer CB0[12], immediateIndexed
dcl_constantbuffer CB1[1], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_output_siv o0.xyzw, position
dcl_temps 1
mad r0.xyz, v1.xyzx, cb1[0].xxxx, v0.xyzx
mov r0.w, l(1.000000)
dp4 o0.x, r0.xyzw, cb0[8].xyzw
dp4 o0.y, r0.xyzw, cb0[9].xyzw
dp4 o0.z, r0.xyzw, cb0[10].xyzw
dp4 o0.w, r0.xyzw, cb0[11].xyzw
ret 
// Approximately 7 instruction slots used