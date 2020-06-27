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
//   bool normalMapEnabled;             // Offset:    0 Size:     4
//   bool specularMapEnabled;           // Offset:    4 Size:     4
//   bool hasGloss;                     // Offset:    8 Size:     4
//   float specularPowerConst;          // Offset:   12 Size:     4
//   float3 specularColor;              // Offset:   16 Size:    12
//   float specularMapWeight;           // Offset:   28 Size:     4
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
// spec                              texture  float4          2d             t1      1 
// nmap                              texture  float4          2d             t2      1 
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
// Tangent                  0   xyz         2     NONE   float   xyz 
// Bitangent                0   xyz         3     NONE   float   xyz 
// Texcoord                 0   xy          4     NONE   float   xy  
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
dcl_constantbuffer CB1[2], immediateIndexed
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_resource_texture2d (float,float,float,float) t2
dcl_input_ps linear v0.xyz
dcl_input_ps linear v1.xyz
dcl_input_ps linear v2.xyz
dcl_input_ps linear v3.xyz
dcl_input_ps linear v4.xy
dcl_output o0.xyzw
dcl_temps 6
//
// Initial variable locations:
//   v0.x <- viewFragPos.x; v0.y <- viewFragPos.y; v0.z <- viewFragPos.z; 
//   v1.x <- viewNormal.x; v1.y <- viewNormal.y; v1.z <- viewNormal.z; 
//   v2.x <- viewTan.x; v2.y <- viewTan.y; v2.z <- viewTan.z; 
//   v3.x <- viewBitan.x; v3.y <- viewBitan.y; v3.z <- viewBitan.z; 
//   v4.x <- tc.x; v4.y <- tc.y; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 26 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
sample_indexable(texture2d)(float,float,float,float) r0.xyzw, v4.xyxx, t0.xyzw, s0  // r0.x <- dtex.x; r0.y <- dtex.y; r0.z <- dtex.z; r0.w <- dtex.w

#line 39
dp3 r1.x, v1.xyzx, v1.xyzx
rsq r1.x, r1.x
mul r1.xyz, r1.xxxx, v1.xyzx  // r1.x <- viewNormal.x; r1.y <- viewNormal.y; r1.z <- viewNormal.z

#line 41
ine r1.w, l(0, 0, 0, 0), cb1[0].x
if_nz r1.w

#line 43
  nop 
  dp3 r1.w, v2.xyzx, v2.xyzx
  rsq r1.w, r1.w
  mul r2.xyz, r1.wwww, v2.xyzx
  dp3 r1.w, v3.xyzx, v3.xyzx
  rsq r1.w, r1.w
  mul r3.xyz, r1.wwww, v3.xyzx
  nop 
  nop 

#line 10 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
  mov r4.x, r2.x  // r4.x <- tanToTarget._m00
  mov r4.y, r3.x  // r4.y <- tanToTarget._m10
  mov r4.z, r1.x  // r4.z <- tanToTarget._m20
  mov r5.x, r2.y  // r5.x <- tanToTarget._m01
  mov r5.y, r3.y  // r5.y <- tanToTarget._m11
  mov r5.z, r1.y  // r5.z <- tanToTarget._m21
  mov r1.x, r2.z  // r1.x <- tanToTarget._m02
  mov r1.y, r3.z  // r1.y <- tanToTarget._m12
  mov r1.z, r1.z  // r1.z <- tanToTarget._m22

#line 12
  sample_indexable(texture2d)(float,float,float,float) r2.xyz, v4.xyxx, t2.xyzw, s0  // r2.x <- normalSample.x; r2.y <- normalSample.y; r2.z <- normalSample.z

#line 13
  mul r2.xyz, r2.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000)
  mov r3.xyz, l(-1.000000,-1.000000,-1.000000,-0.000000)
  add r2.xyz, r2.xyzx, r3.xyzx  // r2.x <- tanNormal.x; r2.y <- tanNormal.y; r2.z <- tanNormal.z

#line 15
  dp3 r3.x, r2.xyzx, r4.xyzx
  dp3 r3.y, r2.xyzx, r5.xyzx
  dp3 r3.z, r2.xyzx, r1.xyzx
  dp3 r1.w, r3.xyzx, r3.xyzx
  rsq r1.w, r1.w
  mul r1.xyz, r1.wwww, r3.xyzx  // r1.x <- <MapNormal return value>.x; r1.y <- <MapNormal return value>.y; r1.z <- <MapNormal return value>.z

#line 43 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
  mov r1.xyz, r1.xyzx  // r1.x <- viewNormal.x; r1.y <- viewNormal.y; r1.z <- viewNormal.z

#line 44
endif 

#line 46
nop 

#line 11 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\LightVectorData.hlsli"
mov r2.xyz, -v0.xyzx
add r2.xyz, r2.xyzx, cb0[0].xyzx  // r2.x <- lv.vToL.x; r2.y <- lv.vToL.y; r2.z <- lv.vToL.z

#line 12
dp3 r1.w, r2.xyzx, r2.xyzx
sqrt r1.w, r1.w  // r1.w <- lv.distToL

#line 13
div r3.xyz, r2.xyzx, r1.wwww  // r3.x <- lv.dirToL.x; r3.y <- lv.dirToL.y; r3.z <- lv.dirToL.z

#line 49 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
mov r2.w, cb1[0].w  // r2.w <- specularPower

#line 50
ine r3.w, l(0, 0, 0, 0), cb1[0].y
if_nz r3.w

#line 52
  sample_indexable(texture2d)(float,float,float,float) r4.xyzw, v4.xyxx, t1.xyzw, s0  // r4.x <- specularSample.x; r4.y <- specularSample.y; r4.z <- specularSample.z; r4.w <- specularSample.w

#line 53
  mul r4.xyz, r4.xyzx, cb1[1].wwww  // r4.x <- specularReflectionColor.x; r4.y <- specularReflectionColor.y; r4.z <- specularReflectionColor.z

#line 54
  ine r3.w, l(0, 0, 0, 0), cb1[0].z
  if_nz r3.w

#line 56
    mul r3.w, r4.w, l(13.000000)
    log r4.w, l(2.000000)
    mul r3.w, r3.w, r4.w
    exp r2.w, r3.w

#line 57
  endif 

#line 58
else 

#line 61
  mov r4.xyz, cb1[1].xyzx  // r4.x <- specularReflectionColor.x; r4.y <- specularReflectionColor.y; r4.z <- specularReflectionColor.z

#line 62
endif 

#line 64
nop 
mov r3.w, cb0[3].x
mov r4.w, cb0[3].y
mov r5.x, cb0[3].z

#line 20 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
mul r4.w, r1.w, r4.w
add r3.w, r3.w, r4.w
mul r1.w, r1.w, r1.w
mul r1.w, r1.w, r5.x
add r1.w, r1.w, r3.w
div r1.w, l(1.000000), r1.w  // r1.w <- <Attenuate return value>

#line 66 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
nop 
mov r5.xyz, cb0[2].xyzx
mov r3.w, cb0[2].w

#line 30 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
mul r5.xyz, r3.wwww, r5.xyzx
mul r5.xyz, r1.wwww, r5.xyzx
dp3 r3.x, r3.xyzx, r1.xyzx
max r3.x, r3.x, l(0.000000)
mul r3.xyz, r3.xxxx, r5.xyzx  // r3.x <- <Diffuse return value>.x; r3.y <- <Diffuse return value>.y; r3.z <- <Diffuse return value>.z

#line 66 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
mov r3.xyz, r3.xyzx  // r3.x <- diffuse.x; r3.y <- diffuse.y; r3.z <- diffuse.z

#line 68
nop 
mov r3.w, l(1.000000)

#line 43 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\Common\ShaderOps.hlsli"
dp3 r4.w, r2.xyzx, r1.xyzx
mul r1.xyz, r1.xyzx, r4.wwww  // r1.x <- w.x; r1.y <- w.y; r1.z <- w.z

#line 44
mul r1.xyz, r1.xyzx, l(2.000000, 2.000000, 2.000000, 0.000000)
mov r2.xyz, -r2.xyzx
add r1.xyz, r1.xyzx, r2.xyzx
dp3 r2.x, r1.xyzx, r1.xyzx
rsq r2.x, r2.x
mul r1.xyz, r1.xyzx, r2.xxxx  // r1.x <- r.x; r1.y <- r.y; r1.z <- r.z

#line 46
dp3 r2.x, v0.xyzx, v0.xyzx
rsq r2.x, r2.x
mul r2.xyz, r2.xxxx, v0.xyzx  // r2.x <- viewCamToFrag.x; r2.y <- viewCamToFrag.y; r2.z <- viewCamToFrag.z

#line 49
mul r4.xyz, r4.xyzx, r1.wwww
mul r4.xyz, r3.wwww, r4.xyzx
mov r1.xyz, -r1.xyzx
dp3 r1.x, r1.xyzx, r2.xyzx
max r1.x, r1.x, l(0.000000)
log r1.x, r1.x
mul r1.x, r1.x, r2.w
exp r1.x, r1.x
mul r1.xyz, r1.xxxx, r4.xyzx  // r1.x <- <Speculate return value>.x; r1.y <- <Speculate return value>.y; r1.z <- <Speculate return value>.z

#line 68 "F:\MyRepo\DirectXRenderer\Sandbox\asset\shader\PhongSpecNormalMap_ps.hlsl"
mov r1.xyz, r1.xyzx  // r1.x <- specularReflected.x; r1.y <- specularReflected.y; r1.z <- specularReflected.z

#line 73
add r2.xyz, r3.xyzx, cb0[1].xyzx
mul r0.xyz, r0.xyzx, r2.xyzx
add r0.xyz, r1.xyzx, r0.xyzx
max r0.xyz, r0.xyzx, l(0.000000, 0.000000, 0.000000, 0.000000)
min o0.xyz, r0.xyzx, l(1.000000, 1.000000, 1.000000, 0.000000)
mov o0.w, r0.w
ret 
// Approximately 106 instruction slots used
