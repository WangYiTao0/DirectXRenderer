//// Created by inigo quilez - iq/2013
//// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.


//// on the derivatives based noise: http://iquilezles.org/www/articles/morenoise/morenoise.htm
//// on the soft shadow technique: http://iquilezles.org/www/articles/rmshadows/rmshadows.htm
//// on the fog calculations: http://iquilezles.org/www/articles/fog/fog.htm
//// on the lighting: http://iquilezles.org/www/articles/outdoorslighting/outdoorslighting.htm
//// on the raymarching: http://iquilezles.org/www/articles/terrainmarching/terrainmarching.htm
//#include "defines.hlsli"
//#include "ShaderToy.hlsli"

//#define AA 1   // make this 2 or even 3 if you have a really powerful GPU


//#define SC (250.0)

//// value noise, and its analytical derivatives
//float3 noised(in float2 x)
//{
//    float2 f = fract(x);
//    float2 u = f * f * (3.0 - 2.0 * f);

//#if 1
//    // texel fetch version
//    ivec2 p = ivec2(floor(x));
//    float a = texelFetch(iChannel0, (p + ivec2(0, 0)) & 255, 0).x;
//    float b = texelFetch(iChannel0, (p + ivec2(1, 0)) & 255, 0).x;
//    float c = texelFetch(iChannel0, (p + ivec2(0, 1)) & 255, 0).x;
//    float d = texelFetch(iChannel0, (p + ivec2(1, 1)) & 255, 0).x;
//#else    
//    // texture version    
//    float2 p = floor(x);
//	float a = textureLod( iChannel0, (p+float2(0.5,0.5))/256.0, 0.0 ).x;
//	float b = textureLod( iChannel0, (p+float2(1.5,0.5))/256.0, 0.0 ).x;
//	float c = textureLod( iChannel0, (p+float2(0.5,1.5))/256.0, 0.0 ).x;
//	float d = textureLod( iChannel0, (p+float2(1.5,1.5))/256.0, 0.0 ).x;
//#endif
    
//    return float3(a + (b - a) * u.x + (c - a) * u.y + (a - b - c + d) * u.x * u.y,
//				6.0 * f * (1.0 - f) * (float2(b - a, c - a) + (a - b - c + d) * u.yx));
//}

//const mat2 m2 = mat2(0.8, -0.6, 0.6, 0.8);


//float terrainH(in float2 x)
//{
//    float2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    float2 d = float2(0.0);
//    for (int i = 0; i < 16; i++)
//    {
//        float3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = m2 * p * 2.0;
//    }

//    return SC * 120.0 * a;
//}

//float terrainM(in float2 x)
//{
//    float2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    float2 d = float2(0.0);
//    for (int i = 0; i < 9; i++)
//    {
//        float3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = m2 * p * 2.0;
//    }
//    return SC * 120.0 * a;
//}

//float terrainL(in float2 x)
//{
//    float2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    float2 d = float2(0.0);
//    for (int i = 0; i < 3; i++)
//    {
//        float3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = m2 * p * 2.0;
//    }

//    return SC * 120.0 * a;
//}

//float raycast(in float3 ro, in float3 rd, in float tmin, in float tmax)
//{
//    float t = tmin;
//    for (int i = 0; i < 300; i++)
//    {
//        float3 pos = ro + t * rd;
//        float h = pos.y - terrainM(pos.xz);
//        if (abs(h) < (0.0015 * t) || t > tmax)
//            break;
//        t += 0.4 * h;
//    }

//    return t;
//}

//float softShadow(in float3 ro, in float3 rd)
//{
//    float res = 1.0;
//    float t = 0.001;
//    for (int i = 0; i < 80; i++)
//    {
//        float3 p = ro + t * rd;
//        float h = p.y - terrainM(p.xz);
//        res = min(res, 16.0 * h / t);
//        t += h;
//        if (res < 0.001 || p.y > (SC * 200.0))
//            break;
//    }
//    return clamp(res, 0.0, 1.0);
//}

//float3 calcNormal(in float3 pos, float t)
//{
//    float2 eps = float2(0.001 * t, 0.0);
//    return normalize(float3(terrainH(pos.xz - eps.xy) - terrainH(pos.xz + eps.xy),
//                            2.0 * eps.x,
//                            terrainH(pos.xz - eps.yx) - terrainH(pos.xz + eps.yx)));
//}

//float fbm(float2 p)
//{
//    float f = 0.0;
//    f += 0.5000 * texture(iChannel0, p / 256.0).x;
//    p = m2 * p * 2.02;
//    f += 0.2500 * texture(iChannel0, p / 256.0).x;
//    p = m2 * p * 2.03;
//    f += 0.1250 * texture(iChannel0, p / 256.0).x;
//    p = m2 * p * 2.01;
//    f += 0.0625 * texture(iChannel0, p / 256.0).x;
//    return f / 0.9375;
//}

//const float kMaxT = 5000.0 * SC;

//vec4 render(in float3 ro, in float3 rd)
//{
//    float3 light1 = normalize(float3(-0.8, 0.4, -0.3));
//    // bounding plane
//    float tmin = 1.0;
//    float tmax = kMaxT;
//#if 1
//    float maxh = 300.0 * SC;
//    float tp = (maxh - ro.y) / rd.y;
//    if (tp > 0.0)
//    {
//        if (ro.y > maxh)
//            tmin = max(tmin, tp);
//        else
//            tmax = min(tmax, tp);
//    }
//#endif
//    float sundot = clamp(dot(rd, light1), 0.0, 1.0);
//    float3 col;
//    float t = raycast(ro, rd, tmin, tmax);
//    if (t > tmax)
//    {
//        // sky		
//        col = float3(0.3, 0.5, 0.85) - rd.y * rd.y * 0.5;
//        col = mix(col, 0.85 * float3(0.7, 0.75, 0.85), pow(1.0 - max(rd.y, 0.0), 4.0));
//        // sun
//        col += 0.25 * float3(1.0, 0.7, 0.4) * pow(sundot, 5.0);
//        col += 0.25 * float3(1.0, 0.8, 0.6) * pow(sundot, 64.0);
//        col += 0.2 * float3(1.0, 0.8, 0.6) * pow(sundot, 512.0);
//        // clouds
//        float2 sc = ro.xz + rd.xz * (SC * 1000.0 - ro.y) / rd.y;
//        col = mix(col, float3(1.0, 0.95, 1.0), 0.5 * smoothstep(0.5, 0.8, fbm(0.0005 * sc / SC)));
//        // horizon
//        col = mix(col, 0.68 * float3(0.4, 0.65, 1.0), pow(1.0 - max(rd.y, 0.0), 16.0));
//        t = -1.0;
//    }
//    else
//    {
//        // mountains		
//        float3 pos = ro + t * rd;
//        float3 nor = calcNormal(pos, t);
//        //nor = normalize( nor + 0.5*( float3(-1.0,0.0,-1.0) + float3(2.0,1.0,2.0)*texture(iChannel1,0.01*pos.xz).xyz) );
//        float3 ref = reflect(rd, nor);
//        float fre = clamp(1.0 + dot(rd, nor), 0.0, 1.0);
//        float3 hal = normalize(light1 - rd);
        
//        // rock
//        float r = texture(iChannel0, (7.0 / SC) * pos.xz / 256.0).x;
//        col = (r * 0.25 + 0.75) * 0.9 * mix(float3(0.08, 0.05, 0.03), float3(0.10, 0.09, 0.08),
//                                     texture(iChannel0, 0.00007 * float2(pos.x, pos.y * 48.0) / SC).x);
//        col = mix(col, 0.20 * float3(0.45, .30, 0.15) * (0.50 + 0.50 * r), smoothstep(0.70, 0.9, nor.y));
        
        
//        col = mix(col, 0.15 * float3(0.30, .30, 0.10) * (0.25 + 0.75 * r), smoothstep(0.95, 1.0, nor.y));
//        col *= 0.1 + 1.8 * sqrt(fbm(pos.xz * 0.04) * fbm(pos.xz * 0.005));

//		// snow
//        float h = smoothstep(55.0, 80.0, pos.y / SC + 25.0 * fbm(0.01 * pos.xz / SC));
//        float e = smoothstep(1.0 - 0.5 * h, 1.0 - 0.1 * h, nor.y);
//        float o = 0.3 + 0.7 * smoothstep(0.0, 0.1, nor.x + h * h);
//        float s = h * e * o;
//        col = mix(col, 0.29 * float3(0.62, 0.65, 0.7), smoothstep(0.1, 0.9, s));
		
//         // lighting		
//        float amb = clamp(0.5 + 0.5 * nor.y, 0.0, 1.0);
//        float dif = clamp(dot(light1, nor), 0.0, 1.0);
//        float bac = clamp(0.2 + 0.8 * dot(normalize(float3(-light1.x, 0.0, light1.z)), nor), 0.0, 1.0);
//        float sh = 1.0;
//        if (dif >= 0.0001)
//            sh = softShadow(pos + light1 * SC * 0.05, light1);
		
//        float3 lin = float3(0.0);
//        lin += dif * float3(8.00, 5.00, 3.00) * 1.3 * float3(sh, sh * sh * 0.5 + 0.5 * sh, sh * sh * 0.8 + 0.2 * sh);
//        lin += amb * float3(0.40, 0.60, 1.00) * 1.2;
//        lin += bac * float3(0.40, 0.50, 0.60);
//        col *= lin;
        
//        col += (0.7 + 0.3 * s) * (0.04 + 0.96 * pow(clamp(1.0 + dot(hal, rd), 0.0, 1.0), 5.0)) *
//               float3(7.0, 5.0, 3.0) * dif * sh *
//               pow(clamp(dot(nor, hal), 0.0, 1.0), 16.0);
        
//        col += s * 0.65 * pow(fre, 4.0) * float3(0.3, 0.5, 0.6) * smoothstep(0.0, 0.6, ref.y);

//        //col = col*3.0/(1.5+col);
        
//		// fog
//        float fo = 1.0 - exp(-pow(0.001 * t / SC, 1.5));
//        float3 fco = 0.65 * float3(0.4, 0.65, 1.0); // + 0.1*float3(1.0,0.8,0.5)*pow( sundot, 4.0 );
//        col = mix(col, fco, fo);

//    }
//    // sun scatter
//    col += 0.3 * float3(1.0, 0.7, 0.3) * pow(sundot, 8.0);

//    // gamma
//    col = sqrt(col);
    
//    return vec4(col, t);
//}

//float3 camPath(float time)
//{
//    return SC * 1100.0 * float3(cos(0.0 + 0.23 * time), 0.0, cos(1.5 + 0.21 * time));
//}

//mat3 setCamera(in float3 ro, in float3 ta, in float cr)
//{
//    float3 cw = normalize(ta - ro);
//    float3 cp = float3(sin(cr), cos(cr), 0.0);
//    float3 cu = normalize(cross(cw, cp));
//    float3 cv = normalize(cross(cu, cw));
//    return mat3(cu, cv, cw);
//}

//void moveCamera(float time, out float3 oRo, out float3 oTa, out float oCr, out float oFl)
//{
//    float3 ro = camPath(time);
//    float3 ta = camPath(time + 3.0);
//    ro.y = terrainL(ro.xz) + 22.0 * SC;
//    ta.y = ro.y - 20.0 * SC;
//    float cr = 0.2 * cos(0.1 * time);
//    oRo = ro;
//    oTa = ta;
//    oCr = cr;
//    oFl = 3.0;
//}

//void mainImage(out vec4 fragColor, in float2 fragCoord)
//{
//    float time = iTime * 0.1 - 0.1 + 0.3 + 4.0 * iMouse.x / iResolution.x;

//    // camera position
//    float3 ro, ta;
//    float cr, fl;
//    moveCamera(time, ro, ta, cr, fl);

//    // camera2world transform    
//    mat3 cam = setCamera(ro, ta, cr);

//    // pixel
//    float2 p = (-iResolution.xy + 2.0 * fragCoord) / iResolution.y;

//    float t = kMaxT;
//    float3 tot = float3(0.0);
//#if AA>1
//    for( int m=0; m<AA; m++ )
//    for( int n=0; n<AA; n++ )
//    {
//        // pixel coordinates
//        float2 o = float2(float(m),float(n)) / float(AA) - 0.5;
//        float2 s = (-iResolution.xy + 2.0*(fragCoord+o))/iResolution.y;
//#else    
//    float2 s = p;
//#endif

//        // camera ray    
//    float3 rd = cam * normalize(float3(s, fl));

//    vec4 res = render(ro, rd);
//    t = min(t, res.w);
 
//    tot += res.xyz;
//#if AA>1
//    }
//    tot /= float(AA*AA);
//#endif


//    //-------------------------------------
//	// velocity vectors (through depth reprojection)
//    //-------------------------------------
//    float vel = 0.0;
//    if (t < 0.0)
//    {
//        vel = -1.0;
//    }
//    else
//    {

//        // old camera position
//        float oldTime = time - 0.1 * 1.0 / 24.0; // 1/24 of a second blur
//        float3 oldRo, oldTa;
//        float oldCr, oldFl;
//        moveCamera(oldTime, oldRo, oldTa, oldCr, oldFl);
//        mat3 oldCam = setCamera(oldRo, oldTa, oldCr);

//        // world space
//#if AA>1
//        float3 rd = cam * normalize(float3(p,fl));
//#endif
//        float3 wpos = ro + rd * t;
//        // camera space
//        float3 cpos = float3(dot(wpos - oldRo, oldCam[0]),
//                          dot(wpos - oldRo, oldCam[1]),
//                          dot(wpos - oldRo, oldCam[2]));
//        // ndc space
//        float2 npos = oldFl * cpos.xy / cpos.z;
//        // screen space
//        float2 spos = 0.5 + 0.5 * npos * float2(iResolution.y / iResolution.x, 1.0);


//        // compress velocity vector in a single float
//        float2 uv = fragCoord / iResolution.xy;
//        spos = clamp(0.5 + 0.5 * (spos - uv) / 0.25, 0.0, 1.0);
//        vel = floor(spos.x * 255.0) + floor(spos.y * 255.0) * 256.0;
//    }
    
//    fragColor = vec4(tot, vel);
//}