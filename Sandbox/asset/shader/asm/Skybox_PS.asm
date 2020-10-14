//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// sam                               sampler      NA          NA             s0      1 
// tex                               texture  float4        cube             t0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed
dcl_sampler s0, mode_default
dcl_resource_texturecube (float,float,float,float) t0
dcl_input_ps linear v0.xyz
dcl_output o0.xyzw
sample_indexable(texturecube)(float,float,float,float) o0.xyzw, v0.xyzx, t0.xyzw, s0
ret 
// Approximately 2 instruction slots used
