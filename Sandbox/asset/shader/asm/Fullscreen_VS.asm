//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xy          0     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Texcoord                 0   xy          0     NONE   float   xy  
// SV_Position              0   xyzw        1      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed
dcl_input v0.xy
dcl_output o0.xy
dcl_output_siv o1.xyzw, position
dcl_temps 1
add r0.xy, v0.xyxx, l(1.000000, -1.000000, 0.000000, 0.000000)
mul o0.xy, r0.xyxx, l(0.500000, -0.500000, 0.000000, 0.000000)
mov o1.xy, v0.xyxx
mov o1.zw, l(0,0,0,1.000000)
ret 
// Approximately 5 instruction slots used