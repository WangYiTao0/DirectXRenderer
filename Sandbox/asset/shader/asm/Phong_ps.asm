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
//   float3 materialColor;              // Offset:    0 Size:    12
//   float3 specularColor;              // Offset:   16 Size:    12
//   float specularWeight;              // Offset:   28 Size:     4
//   float specularGloss;               // Offset:   32 Size:     4
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
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
dcl_constantbuffer CB1[3], immediateIndexed
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_output o0.xyzw
dcl_temps 4
//
// Initial variable locations:
//   v0.x <- viewFragPos.x; v0.y <- viewFragPos.y; v0.z <- viewFragPos.z; 
//   v1.x <- viewNormal.x; v1.y <- viewNormal.y; v1.z <- viewNormal.z; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 18 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_PS.hlsl"
dp3 r0.x, v1.xyzx, v1.xyzx
rsq r0.x, r0.x
mul r0.xyz, r0.xxxx, v1.xyzx  // r0.x <- viewNormal.x; r0.y <- viewNormal.y; r0.z <- viewNormal.z

#line 20
nop 

#line 11 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\LightVectorData.hlsli"
mov r1.xyz, -v0.xyzx
add r1.xyz, r1.xyzx, cb0[0].xyzx  // r1.x <- lv.vToL.x; r1.y <- lv.vToL.y; r1.z <- lv.vToL.z

#line 12
dp3 r0.w, r1.xyzx, r1.xyzx
sqrt r0.w, r0.w  // r0.w <- lv.distToL

#line 13
div r2.xyz, r1.xyzx, r0.wwww  // r2.x <- lv.dirToL.x; r2.y <- lv.dirToL.y; r2.z <- lv.dirToL.z

#line 22 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_PS.hlsl"
nop 
mov r1.w, cb0[3].x
mov r2.w, cb0[3].y
mov r3.x, cb0[3].z

#line 20 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
mul r2.w, r0.w, r2.w
add r1.w, r1.w, r2.w
mul r0.w, r0.w, r0.w
mul r0.w, r0.w, r3.x
add r0.w, r0.w, r1.w
div r0.w, l(1.000000), r0.w  // r0.w <- <Attenuate return value>

#line 24 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_PS.hlsl"
nop 
mov r3.xyz, cb0[2].xyzx
mov r1.w, cb0[2].w

#line 30 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
mul r3.xyz, r1.wwww, r3.xyzx
mul r3.xyz, r0.wwww, r3.xyzx
dp3 r1.w, r2.xyzx, r0.xyzx
max r1.w, r1.w, l(0.000000)
mul r2.xyz, r1.wwww, r3.xyzx  // r2.x <- <Diffuse return value>.x; r2.y <- <Diffuse return value>.y; r2.z <- <Diffuse return value>.z

#line 24 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_PS.hlsl"
mov r2.xyz, r2.xyzx  // r2.x <- diffuse.x; r2.y <- diffuse.y; r2.z <- diffuse.z

#line 26
nop 
mul r3.xyz, cb0[2].wwww, cb0[2].xyzx
mul r3.xyz, r3.xyzx, cb1[1].xyzx
mov r1.w, cb1[1].w

#line 43 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
dp3 r2.w, r1.xyzx, r0.xyzx
mul r0.xyz, r0.xyzx, r2.wwww  // r0.x <- w.x; r0.y <- w.y; r0.z <- w.z

#line 44
mul r0.xyz, r0.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000)
mov r1.xyz, -r1.xyzx
add r0.xyz, r0.xyzx, r1.xyzx
dp3 r1.x, r0.xyzx, r0.xyzx
rsq r1.x, r1.x
mul r0.xyz, r0.xyzx, r1.xxxx  // r0.x <- r.x; r0.y <- r.y; r0.z <- r.z

#line 46
dp3 r1.x, v0.xyzx, v0.xyzx
rsq r1.x, r1.x
mul r1.xyz, r1.xxxx, v0.xyzx  // r1.x <- viewCamToFrag.x; r1.y <- viewCamToFrag.y; r1.z <- viewCamToFrag.z

#line 49
mul r3.xyz, r0.wwww, r3.xyzx
mul r3.xyz, r1.wwww, r3.xyzx
mov r0.xyz, -r0.xyzx
dp3 r0.x, r0.xyzx, r1.xyzx
max r0.x, r0.x, l(0.000000)
log r0.x, r0.x
mul r0.x, r0.x, cb1[2].x
exp r0.x, r0.x
mul r0.xyz, r0.xxxx, r3.xyzx  // r0.x <- <Speculate return value>.x; r0.y <- <Speculate return value>.y; r0.z <- <Speculate return value>.z

#line 26 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Phong_PS.hlsl"
mov r0.xyz, r0.xyzx  // r0.x <- specular.x; r0.y <- specular.y; r0.z <- specular.z

#line 31
add r1.xyz, r2.xyzx, cb0[1].xyzx
mul r1.xyz, r1.xyzx, cb1[0].xyzx
add r0.xyz, r0.xyzx, r1.xyzx
max r0.xyz, r0.xyzx, l(0.000000, 0.000000, 0.000000, 0.000000)
min o0.xyz, r0.xyzx, l(1.000000, 1.000000, 1.000000, 0.000000)
mov o0.w, l(1.000000)
ret 
// Approximately 60 instruction slots used
