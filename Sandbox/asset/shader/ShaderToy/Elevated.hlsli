////Atmospheric Scattering From Rendering out-door light scattering in real time.
////https://www.shadertoy.com/view/WtBXWw
////By Naty Hoffmann and Arcot J. Preetham.
////http://renderwonk.com/publications/gdm-2002/GDM_August_2002.pdf
////Combined with the Atmospheric Scattering Foggy Scene "Elevated"
////https://www.shadertoy.com/view/MdX3Rr

//#include "defines.hlsli"
//#include "ShaderToy.hlsli"

//#define Gamma 1.4
//#define fov tan(radians(60.0))
//#define autoCamera 1

//#define DetectSunMode 1 //This would be slower,but looks much better 

//#define Rayleigh 1.
//#define Mie 1.

//#define RayleighAtt 1.
//#define MieAtt 1.2
//#define DistanceAtt 1e-5

//#define skyInt 1.4

////float g = -0.84;
////float g = -0.97;
//float g = -0.93;
//float gS = -0.43;

//#if 1
//vec3 _betaR = vec3(1.95e-2, 1.1e-1, 2.94e-1);
//vec3 _betaM = vec3(4e-2, 4e-2, 4e-2);
//#else
//vec3 _betaR = vec3(6.95e-2, 1.18e-1, 2.44e-1); 
//vec3 _betaM = vec3(4e-2, 4e-2, 4e-2);
//#endif

//vec3 Ds = normalize(vec3(0., 0., -1.)); //sun 

//#define AA 1   // make this 2 or even 3 if you have a really powerful GPU

//#define SC (250.0)

//// value noise, and its analytical derivatives
//vec3 noised(in vec2 x)
//{
//    vec2 f = fract(x);
//    vec2 u = f * f * (3.0 - 2.0 * f);

//#if 1
//    // texel fetch version
//    ivec2 p = ivec2(floor(x));
//    float a = iChannel1.SampleLevel(splr, (p + vec2(0.5, 0.5)) / 256.0, 0.0).x;
//    float b = iChannel1.SampleLevel(splr, (p + vec2(1.5, 0.5)) / 256.0, 0.0).x;
//    float c = iChannel1.SampleLevel(splr, (p + vec2(0.5, 1.5)) / 256.0, 0.0).x;
//    float d = iChannel1.SampleLevel(splr, (p + vec2(1.5, 1.5)) / 256.0, 0.0).x;
//#else    
//    // texture version    
//    vec2 p = floor(x);
//	float a = textureLod( iChannel0, (p+vec2(0.5,0.5))/256.0, 0.0 ).x;
//	float b = textureLod( iChannel0, (p+vec2(1.5,0.5))/256.0, 0.0 ).x;
//	float c = textureLod( iChannel0, (p+vec2(0.5,1.5))/256.0, 0.0 ).x;
//	float d = textureLod( iChannel0, (p+vec2(1.5,1.5))/256.0, 0.0 ).x;
//#endif
    
//    return vec3(a + (b - a) * u.x + (c - a) * u.y + (a - b - c + d) * u.x * u.y,
//				6.0 * f * (1.0 - f) * (vec2(b - a, c - a) + (a - b - c + d) * u.yx));
//}

//static const mat2 m2 = mat2(0.8, -0.6, 0.6, 0.8);


//float terrainH(in vec2 x)
//{
//    vec2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    vec2 d = vec2(0.0, 0.0);
//    for (int i = 0; i < 15; i++)
//    {
//        vec3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = mul(m2, p) * 2.0;
//    }

//    return SC * 120.0 * a;
//}

//float terrainM(in vec2 x)
//{
//    vec2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    vec2 d = vec2(0.0, 0.0);
//    for (int i = 0; i < 9; i++)
//    {
//        vec3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = mul(m2, p) * 2.0;
//    }
//    return SC * 120.0 * a;
//}

//float terrainL(in vec2 x)
//{
//    vec2 p = x * 0.003 / SC;
//    float a = 0.0;
//    float b = 1.0;
//    vec2 d = vec2(0.0, 0.0);
//    for (int i = 0; i < 3; i++)
//    {
//        vec3 n = noised(p);
//        d += n.yz;
//        a += b * n.x / (1.0 + dot(d, d));
//        b *= 0.5;
//        p = mul(m2, p) * 2.0;
//    }

//    return SC * 120.0 * a;
//}

//float interesct(in vec3 ro, in vec3 rd, in float tmin, in float tmax)
//{
//    float t = tmin;
//    for (int i = 0; i < 300; i++)
//    {
//        vec3 pos = ro + t * rd;
//        float h = pos.y - terrainM(pos.xz);
//        if (abs(h) < (0.002 * t) || t > tmax)
//            break;
//        t += 0.4 * h;
//    }

//    return t;
//}

//float softShadow(in vec3 ro, in vec3 rd)
//{
//    float res = 1.0;
//    float t = 0.001;
//    for (int i = 0; i < 80; i++)
//    {
//        vec3 p = ro + t * rd;
//        float h = p.y - terrainM(p.xz);
//        res = min(res, 16.0 * h / t);
//        t += h;
//        if (res < 0.001 || p.y > (SC * 200.0))
//            break;
//    }
//    return clamp(res, 0.0, 1.0);
//}

//vec3 calcNormal(in vec3 pos, float t)
//{
//    vec2 eps = vec2(0.002 * t, 0.0);
//    return normalize(vec3(terrainH(pos.xz - eps.xy) - terrainH(pos.xz + eps.xy),
//                            2.0 * eps.x,
//                            terrainH(pos.xz - eps.yx) - terrainH(pos.xz + eps.yx)));
//}

//vec3 calcAtmosphericScattering(float sR, float sM, out vec3 extinction, float cosine, float g1)
//{
//    extinction = exp(-(_betaR * sR + _betaM * sM));

//    // scattering phase
//    float g2 = g1 * g1;
//    float fcos2 = cosine * cosine;
//    float miePhase = Mie * pow(1. + g2 + 2. * g1 * cosine, -1.5) * (1. - g2) / (2. + g2);
//    //g = 0;
//    float rayleighPhase = Rayleigh;

//    vec3 inScatter = (1. + fcos2) * vec3(rayleighPhase + _betaM / _betaR * miePhase);
    
//    return inScatter;
//}


//float fbm(vec2 p)
//{
//    float f = 0.0;
//    //texture(iChannel1, p / 256.0)
//    iChannel1.Sample(splr, p / 256.0);
//    f += 0.5000 * iChannel1.Sample(splr, p / 256.0).x;
//    p = mul(m2, p) * 2.02;
//    f += 0.2500 * iChannel1.Sample(splr, p / 256.0).x;
//    p = mul(m2, p) * 2.03;
//    f += 0.1250 * iChannel1.Sample(splr, p / 256.0).x;
//    p = mul(m2, p) * 2.01;
//    f += 0.0625 * iChannel1.Sample(splr, p / 256.0).x;
//    return f / 0.9375;
//}

//static const float kMaxT = 5000.0 * SC;

//vec3 ACESFilm(vec3 x)
//{
//    float tA = 2.51;
//    float tB = 0.03;
//    float tC = 2.43;
//    float tD = 0.59;
//    float tE = 0.14;
//    return clamp((x * (tA * x + tB)) / (x * (tC * x + tD) + tE), 0.0, 1.0);
//}

//vec4 render(in vec3 ro, in vec3 rd, vec3 light1)
//{
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
    
//    vec3 extinction;
    
    

//    // optical depth -> zenithAngle
//    float zenithAngle = max(0., rd.y); //abs( rd.y);
//    float sR = RayleighAtt / zenithAngle;
//    float sM = MieAtt / zenithAngle;

//    vec3 inScatter = calcAtmosphericScattering(sR, sM, extinction, sundot, g);
//    vec3 skyCol = inScatter * (1.0 - extinction);

//    vec3 col;
//    float t = interesct(ro, rd, tmin, tmax);
//    if (t > tmax)
//    {
//        // sky	
//        col = skyCol; // *vec3(1.6,1.4,1.0)
            
//        // sun
//        col += 0.47 * vec3(1.6, 1.4, 1.0) * pow(sundot, 350.0) * extinction;
//        // sun haze
//        col += 0.4 * vec3(0.8, 0.9, 1.0) * pow(sundot, 2.0) * extinction;
        
//        // clouds
//        vec2 sc = ro.xz + rd.xz * (SC * 1000.0 - ro.y) / rd.y;
//        col += 2. * vec3(1.0, 0.95, 1.0) * extinction * smoothstep(0.5, 0.8, fbm(0.0005 * sc / SC));
        
//        t = -1.0;
//    }
//    else
//    {
//        // mountains		
//        vec3 pos = ro + t * rd;
//        vec3 nor = calcNormal(pos, t);
//        //nor = normalize( nor + 0.5*( vec3(-1.0,0.0,-1.0) + vec3(2.0,1.0,2.0)*texture(iChannel1,0.01*pos.xz).xyz) );
//        vec3 ref = reflect(rd, nor);
//        float fre = clamp(1.0 + dot(rd, nor), 0.0, 1.0);
//        vec3 hal = normalize(light1 - rd);
        
//        // rock
//        float r = iChannel1.Sample(splr, (7.0 / SC) * pos.xz / 256.0).x;
//        col = (r * 0.25 + 0.75) * 0.9 * mix(vec3(0.08, 0.05, 0.03), vec3(0.10, 0.09, 0.08),
//                                     iChannel1.Sample(splr, 0.00007 * vec2(pos.x, pos.y * 48.0) / SC).x);
//        col = mix(col, 0.20 * vec3(0.45, .30, 0.15) * (0.50 + 0.50 * r), smoothstep(0.70, 0.9, nor.y));
//        col = mix(col, 0.15 * vec3(0.30, .30, 0.10) * (0.25 + 0.75 * r), smoothstep(0.95, 1.0, nor.y));

//		// snow
//        float h = smoothstep(55.0, 80.0, pos.y / SC + 25.0 * fbm(0.01 * pos.xz / SC));
//        float e = smoothstep(1.0 - 0.5 * h, 1.0 - 0.1 * h, nor.y);
//        float o = 0.3 + 0.7 * smoothstep(0.0, 0.1, nor.x + h * h);
//        float s = h * e * o;
//        col = mix(col, 0.29 * vec3(0.62, 0.65, 0.7), smoothstep(0.1, 0.9, s));
		
//         // lighting		
//        float amb = clamp(0.5 + 0.5 * nor.y, 0.0, 1.0);
//        float dif = clamp(dot(light1, nor), 0.0, 1.0);
//        float bac = clamp(0.2 + 0.8 * dot(normalize(vec3(-light1.x, 0.0, light1.z)), nor), 0.0, 1.0);
//        float sh = 1.0;
//        if (dif >= 0.0001)
//            sh = softShadow(pos + light1 * SC * 0.05, light1);
		
//        vec3 lin = vec3(0.0, 0.0, 0.0);
//        lin += dif * vec3(7.00, 5.00, 3.00) * 1.3 * vec3(sh, sh * sh * 0.5 + 0.5 * sh, sh * sh * 0.8 + 0.2 * sh);
//        lin += amb * vec3(0.40, 0.60, 1.00) * 1.2;
//        lin += bac * vec3(0.40, 0.50, 0.60);
//        col *= lin;
        
//        //col += s*0.1*pow(fre,4.0)*vec3(7.0,5.0,3.0)*sh * pow( clamp(dot(nor,hal), 0.0, 1.0),16.0);
//        col += s *
//               (0.04 + 0.96 * pow(clamp(1.0 + dot(hal, rd), 0.0, 1.0), 5.0)) *
//               vec3(7.0, 5.0, 3.0) * dif * sh *
//               pow(clamp(dot(nor, hal), 0.0, 1.0), 16.0);
        
        
//        col += s * 0.1 * pow(fre, 4.0) * vec3(0.4, 0.5, 0.6) * smoothstep(0.0, 0.6, ref.y);
        
//        vec3 extinction2;
//        // optical depth -> distance
//        float fo = DistanceAtt * t;
//        vec3 inScatter2 = calcAtmosphericScattering(fo, fo, extinction2, sundot, gS);
//        col *= 2.;
//#if DetectSunMode
//        float t2 = interesct(ro, light1, tmin, tmax);
//        col = mix(inScatter2 * mix(vec3(skyInt, skyInt, skyInt), skyCol, smoothstep(0.1, 2.0, t2 / tmax)), col, extinction2);
//#else
// 		col = mix(inScatter2 * mix(vec3(skyInt), skyCol, smoothstep(0.1, 0.5, t / tmax)), col, extinction2);
//#endif
//    }
    
//    // sun scatter
//    //col += 0.3*vec3(1.0,0.7,0.3)*pow( sundot, 8.0 );

//    // gamma
//	//col = sqrt(col);
            
//    col = ACESFilm(col);
//    col = pow(col, vec3(Gamma, Gamma, Gamma));
    
//    return vec4(col, t);
//}

//vec3 camPath(float time)
//{
//    return SC * 1100.0 * vec3(cos(0.0 + 0.23 * time), 0.0, cos(1.5 + 0.21 * time));
//}

//void moveCamera(float time, out vec3 oRo)
//{
//    vec3 ro = camPath(time);
//    ro.y = terrainL(ro.xz) + 19.0 * SC;
//    oRo = ro;
//}

//void ElvatedBufferA(out vec4 fragColor, in vec2 fragCoord)
//{
//#if autoCamera
//    float time = iTime * 0.1;
//#else
//    float time = 12.59*0.5; // 18.94*0.5
//#endif
    
//    float AR = iResolution.x / iResolution.y;
//    float M = 1.0; //canvas.innerWidth/M //canvas.innerHeight/M --res
    
//    vec2 uvMouse = (iMouse.xy / iResolution.xy);
//    uvMouse.x *= AR;
    
//    vec2 uv0 = (fragCoord.xy);
//    uv0 *= M;
//	//uv0.x *= AR;
    
//    vec2 uv = uv0 * (2.0 * M) - (1.0 * M);
//    uv.x *= AR;
    
//    if (uvMouse.y == 0.)
//        uvMouse.y = (0.7 - (0.05 * fov)); //initial view 
//    if (uvMouse.x == 0.)
//        uvMouse.x = (1.0 - (0.05 * fov)); //initial view
    
//    float3 Ds1 = normalize(vec3(uvMouse.x - ((0.5 * AR)), uvMouse.y - 0.5, (fov / -2.0)));
    
//    // camera position
//    vec3 ro;
//    moveCamera(time, ro);

//    vec3 D = normalize(vec3(uv, -(fov * M)));

//    // pixel
//     vec2 p = 2.0 * fragCoord - 1.0;
//    if (iResolution.x > iResolution.y)
//    {
//        p.x *= iResolution.x / iResolution.y;
//    }
//    else
//    {
//        p.y *= iResolution.y / iResolution.x;
//    }

//    float t = kMaxT;
//    vec3 tot = vec3(0.0, 0.0, 0.0);
//#if AA>1
//    for( int m=0; m<AA; m++ )
//    for( int n=0; n<AA; n++ )
//    {
//        // pixel coordinates
//        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
//        vec2 s = (-iResolution.xy + 2.0*(fragCoord+o))/iResolution.y;
//#else    
//    vec2 s = p;
//#endif

//        // camera ray    
//    vec3 rd = D;

//    vec4 res = render(ro, rd, Ds1);
//    t = min(t, res.w);
 
//    tot += res.xyz;
//#if AA>1
//    }
//    tot /= float(AA*AA);
//#endif

//    fragColor = vec4(tot, 1.0);
//}


// Created by inigo quilez - iq/2013
// License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.


// on the derivatives based noise: http://iquilezles.org/www/articles/morenoise/morenoise.htm
// on the soft shadow technique: http://iquilezles.org/www/articles/rmshadows/rmshadows.htm
// on the fog calculations: http://iquilezles.org/www/articles/fog/fog.htm
// on the lighting: http://iquilezles.org/www/articles/outdoorslighting/outdoorslighting.htm
// on the raymarching: http://iquilezles.org/www/articles/terrainmarching/terrainmarching.htm

#include "defines.hlsli"
#include "ShaderToy.hlsli"

//To do ::  hlsl  Sample Texture;

#define AA 1   // make this 2 or even 3 if you have a really powerful GPU


#define SC (250.0)

// value noise, and its analytical derivatives
vec3 noised(in vec2 x)
{
    vec2 f = fract(x);
    vec2 u = f * f * (3.0 - 2.0 * f);
    vec2 p = floor(x);
    float a = iChannel1.SampleLevel(splr, (p + vec2(0.5, 0.5)) / 256.0, 0.0).x;
    float b = iChannel1.SampleLevel(splr, (p + vec2(1.5, 0.5)) / 256.0, 0.0).x;
    float c = iChannel1.SampleLevel(splr, (p + vec2(0.5, 1.5)) / 256.0, 0.0).x;
    float d = iChannel1.SampleLevel(splr, (p + vec2(1.5, 1.5)) / 256.0, 0.0).x;
//#if 0
//    //// texel fetch version
//    //ivec2 p = ivec2(floor(x));
//    //iChannel1.Load((p + ivec2(0, 0)) & 255);
//    //float a = texelFetch(iChannel1, (p + ivec2(0, 0)) & 255, 0).x;
//    //float b = texelFetch(iChannel1, (p + ivec2(1, 0)) & 255, 0).x;
//    //float c = texelFetch(iChannel1, (p + ivec2(0, 1)) & 255, 0).x;
//    //float d = texelFetch(iChannel1, (p + ivec2(1, 1)) & 255, 0).x;
//#else    
//    // texture version    
//    vec2 p = floor(x);
//    float a = iChannel1.SampleLevel(splr, (p + vec2(0.5, 0.5)) / 256.0, 0.0).x;
//    float b = iChannel1.SampleLevel(splr, (p + vec2(1.5, 0.5)) / 256.0, 0.0).x;
//    float c = iChannel1.SampleLevel(splr, (p + vec2(0.5, 1.5)) / 256.0, 0.0).x;
//    float d = iChannel1.SampleLevel(splr, (p + vec2(1.5, 1.5)) / 256.0, 0.0).x;
//	//float a = textureLod( iChannel1, (p+vec2(0.5,0.5))/256.0, 0.0 ).x;
//	//float b = textureLod( iChannel1, (p+vec2(1.5,0.5))/256.0, 0.0 ).x;
//	//float c = textureLod( iChannel1, (p+vec2(0.5,1.5))/256.0, 0.0 ).x;
//	//float d = textureLod( iChannel1, (p+vec2(1.5,1.5))/256.0, 0.0 ).x;
//#endif
    
    return vec3(a + (b - a) * u.x + (c - a) * u.y + (a - b - c + d) * u.x * u.y,
				6.0 * f * (1.0 - f) * (vec2(b - a, c - a) + (a - b - c + d) * u.yx));
}

static const mat2 m2 = mat2(0.8, -0.6, 0.6, 0.8);


float terrainH(in vec2 x)
{
    vec2 p = x * 0.003 / SC;
    float a = 0.0;
    float b = 1.0;
    vec2 d = vec2(0.0, 0.0);
    for (int i = 0; i < 16; i++)
    {
        vec3 n = noised(p);
        d += n.yz;
        a += b * n.x / (1.0 + dot(d, d));
        b *= 0.5;
        p = mul(m2, p) * 2.0;
    }

    return SC * 120.0 * a;
}

float terrainM(in vec2 x)
{
    vec2 p = x * 0.003 / SC;
    float a = 0.0;
    float b = 1.0;
    vec2 d = vec2(0.0, 0.0);
    for (int i = 0; i < 9; i++)
    {
        vec3 n = noised(p);
        d += n.yz;
        a += b * n.x / (1.0 + dot(d, d));
        b *= 0.5;
        p = mul(m2, p) * 2.0;
    }
    return SC * 120.0 * a;
}

float terrainL(in vec2 x)
{
    vec2 p = x * 0.003 / SC;
    float a = 0.0;
    float b = 1.0;
    vec2 d = vec2(0.0, 0.0);
    for (int i = 0; i < 3; i++)
    {
        vec3 n = noised(p);
        d += n.yz;
        a += b * n.x / (1.0 + dot(d, d));
        b *= 0.5;
        p = mul(m2, p) * 2.0;
    }

    return SC * 120.0 * a;
}

float raycast(in vec3 ro, in vec3 rd, in float tmin, in float tmax)
{
    float t = tmin;
    for (int i = 0; i < 300; i++)
    {
        vec3 pos = ro + t * rd;
        float h = pos.y - terrainM(pos.xz);
        if (abs(h) < (0.0015 * t) || t > tmax)
            break;
        t += 0.4 * h;
    }

    return t;
}

float softShadow(in vec3 ro, in vec3 rd)
{
    float res = 1.0;
    float t = 0.001;
    for (int i = 0; i < 80; i++)
    {
        vec3 p = ro + t * rd;
        float h = p.y - terrainM(p.xz);
        res = min(res, 16.0 * h / t);
        t += h;
        if (res < 0.001 || p.y > (SC * 200.0))
            break;
    }
    return clamp(res, 0.0, 1.0);
}

vec3 calcNormal(in vec3 pos, float t)
{
    vec2 eps = vec2(0.001 * t, 0.0);
    return normalize(vec3(terrainH(pos.xz - eps.xy) - terrainH(pos.xz + eps.xy),
                            2.0 * eps.x,
                            terrainH(pos.xz - eps.yx) - terrainH(pos.xz + eps.yx)));
}

float fbm(vec2 p)
{
    float f = 0.0;
    //texture(iChannel1, p / 256.0)
    iChannel1.Sample(splr, p / 256.0);
    f += 0.5000 * iChannel1.Sample(splr, p / 256.0).x;
    p = mul(m2, p) * 2.02;
    f += 0.2500 * iChannel1.Sample(splr, p / 256.0).x;
    p = mul(m2, p) * 2.03;
    f += 0.1250 * iChannel1.Sample(splr, p / 256.0).x;
    p = mul(m2, p) * 2.01;
    f += 0.0625 * iChannel1.Sample(splr, p / 256.0).x;
    return f / 0.9375;
}

static const float kMaxT = 5000.0 * SC;

vec4 render(in vec3 ro, in vec3 rd)
{
    vec3 light1 = normalize(vec3(-0.8, 0.4, -0.3));
    // bounding plane
    float tmin = 1.0;
    float tmax = kMaxT;
#if 1
    float maxh = 300.0 * SC;
    float tp = (maxh - ro.y) / rd.y;
    if (tp > 0.0)
    {
        if (ro.y > maxh)
            tmin = max(tmin, tp);
        else
            tmax = min(tmax, tp);
    }
#endif
    float sundot = clamp(dot(rd, light1), 0.0, 1.0);
    vec3 col;
    float t = raycast(ro, rd, tmin, tmax);
    if (t > tmax)
    {
        // sky		
        col = vec3(0.3, 0.5, 0.85) - rd.y * rd.y * 0.5;
        col = mix(col, 0.85 * vec3(0.7, 0.75, 0.85), pow(1.0 - max(rd.y, 0.0), 4.0));
        // sun
        col += 0.25 * vec3(1.0, 0.7, 0.4) * pow(sundot, 5.0);
        col += 0.25 * vec3(1.0, 0.8, 0.6) * pow(sundot, 64.0);
        col += 0.2 * vec3(1.0, 0.8, 0.6) * pow(sundot, 512.0);
        // clouds
        vec2 sc = ro.xz + rd.xz * (SC * 1000.0 - ro.y) / rd.y;
        col = mix(col, vec3(1.0, 0.95, 1.0), 0.5 * smoothstep(0.5, 0.8, fbm(0.0005 * sc / SC)));
        // horizon
        col = mix(col, 0.68 * vec3(0.4, 0.65, 1.0), pow(1.0 - max(rd.y, 0.0), 16.0));
        t = -1.0;
    }
    else
    {
        // mountains		
        vec3 pos = ro + t * rd;
        vec3 nor = calcNormal(pos, t);
        //nor = normalize( nor + 0.5*( vec3(-1.0,0.0,-1.0) + vec3(2.0,1.0,2.0)*texture(iChannel1,0.01*pos.xz).xyz) );
        vec3 ref = reflect(rd, nor);
        float fre = clamp(1.0 + dot(rd, nor), 0.0, 1.0);
        vec3 hal = normalize(light1 - rd);
        
        // rock
        float r = iChannel1.Sample(splr, (7.0 / SC) * pos.xz / 256.0).x;
        //float r = texture(iChannel1, (7.0 / SC) * pos.xz / 256.0).x;
        col = (r * 0.25 + 0.75) * 0.9 * mix(vec3(0.08, 0.05, 0.03), vec3(0.10, 0.09, 0.08),
        iChannel1.Sample(splr, 0.00007 * vec2(pos.x, pos.y * 48.0) / SC).x); //  texture(iChannel1, 0.00007 * vec2(pos.x, pos.y * 48.0) / SC).x
        
        col = mix(col, 0.20 * vec3(0.45, .30, 0.15) * (0.50 + 0.50 * r), smoothstep(0.70, 0.9, nor.y));
        
        
        col = mix(col, 0.15 * vec3(0.30, .30, 0.10) * (0.25 + 0.75 * r), smoothstep(0.95, 1.0, nor.y));
        col *= 0.1 + 1.8 * sqrt(fbm(pos.xz * 0.04) * fbm(pos.xz * 0.005));

		// snow
        float h = smoothstep(55.0, 80.0, pos.y / SC + 25.0 * fbm(0.01 * pos.xz / SC));
        float e = smoothstep(1.0 - 0.5 * h, 1.0 - 0.1 * h, nor.y);
        float o = 0.3 + 0.7 * smoothstep(0.0, 0.1, nor.x + h * h);
        float s = h * e * o;
        col = mix(col, 0.29 * vec3(0.62, 0.65, 0.7), smoothstep(0.1, 0.9, s));
		
         // lighting		
        float amb = clamp(0.5 + 0.5 * nor.y, 0.0, 1.0);
        float dif = clamp(dot(light1, nor), 0.0, 1.0);
        float bac = clamp(0.2 + 0.8 * dot(normalize(vec3(-light1.x, 0.0, light1.z)), nor), 0.0, 1.0);
        float sh = 1.0;
        if (dif >= 0.0001)
            sh = softShadow(pos + light1 * SC * 0.05, light1);
		
        vec3 lin = vec3(0.0, 0.0, 0.0);
        lin += dif * vec3(8.00, 5.00, 3.00) * 1.3 * vec3(sh, sh * sh * 0.5 + 0.5 * sh, sh * sh * 0.8 + 0.2 * sh);
        lin += amb * vec3(0.40, 0.60, 1.00) * 1.2;
        lin += bac * vec3(0.40, 0.50, 0.60);
        col *= lin;
        
        col += (0.7 + 0.3 * s) * (0.04 + 0.96 * pow(clamp(1.0 + dot(hal, rd), 0.0, 1.0), 5.0)) *
               vec3(7.0, 5.0, 3.0) * dif * sh *
               pow(clamp(dot(nor, hal), 0.0, 1.0), 16.0);
        
        col += s * 0.65 * pow(fre, 4.0) * vec3(0.3, 0.5, 0.6) * smoothstep(0.0, 0.6, ref.y);

        //col = col*3.0/(1.5+col);
        
		// fog
        float fo = 1.0 - exp(-pow(0.001 * t / SC, 1.5));
        vec3 fco = 0.65 * vec3(0.4, 0.65, 1.0); // + 0.1*vec3(1.0,0.8,0.5)*pow( sundot, 4.0 );
        col = mix(col, fco, fo);

    }
    // sun scatter
    col += 0.3 * vec3(1.0, 0.7, 0.3) * pow(sundot, 8.0);

    // gamma
    col = sqrt(col);
    
    return vec4(col, t);
}

vec3 camPath(float time)
{
    return SC * 1100.0 * vec3(cos(0.0 + 0.23 * time), 0.0, cos(1.5 + 0.21 * time));
}

mat3 setCamera(in vec3 ro, in vec3 ta, in float cr)
{
    vec3 cw = normalize(ta - ro);
    vec3 cp = vec3(sin(cr), cos(cr), 0.0);
    vec3 cu = normalize(cross(cw, cp));
    vec3 cv = normalize(cross(cu, cw));
    return mat3(cu, cv, cw);
}

void moveCamera(float time, out vec3 oRo, out vec3 oTa, out float oCr, out float oFl)
{
    vec3 ro = camPath(time);
    vec3 ta = camPath(time + 3.0);
    //ro.y = terrainL(ro.xz) + 22.0 * SC;
    ro.y = 0.;
    for (float i = -.3; i <= .3; i += .1)
    {
        ro.y += terrainL(camPath(time + i).xz);
    }
    ro.y /= 5.;
    ro.y += 17.0 * SC;
    ta.y = ro.y - 20.0 * SC;
    float cr = 0.2 * cos(0.1 * time);
    oRo = ro;
    oTa = ta;
    oCr = cr;
    oFl = 3.0;
}

void ElvatedBufferA(out vec4 fragColor, in vec2 fragCoord)
{
    float time = iTime * 0.1 - 0.1 + 0.3 + 4.0 * iMouse.x / iResolution.x;

    // camera position
    vec3 ro, ta;
    float cr, fl;
    moveCamera(time, ro, ta, cr, fl);

    // camera2world transform    
    mat3 cam = setCamera(ro, ta, cr);

    // pixel
    vec2 p = 2.0 * fragCoord - 1.0;
    if (iResolution.x > iResolution.y)
    {
        p.x *= iResolution.x / iResolution.y;
    }
    else
    {
        p.y *= iResolution.y / iResolution.x;
    }

    float t = kMaxT;
    vec3 tot = vec3(0.0, 0.0, 0.0);
#if AA>1
    for( int m=0; m<AA; m++ )
    for( int n=0; n<AA; n++ )
    {
        // pixel coordinates
        vec2 o = vec2(float(m),float(n)) / float(AA) - 0.5;
        vec2 s = (-iResolution.xy + 2.0*(fragCoord+o))/iResolution.y;
#else    
        vec2 s = p;
#endif

        // camera ray    
        vec3 rd = mul(cam, normalize(vec3(s, fl)));

        vec4 res = render(ro, rd);
    t = min(t, res.w);
 
    tot += res.xyz;
#if AA>1
    }
    tot /= float(AA*AA);
#endif


    //-------------------------------------
	// velocity vectors (through depth reprojection)
    //-------------------------------------
    float vel = 0.0;
    if (t < 0.0)
    {
        vel = -1.0;
    }
    else
    {

        // old camera position
        float oldTime = time - 0.1 * 1.0 / 24.0; // 1/24 of a second blur
        vec3 oldRo, oldTa;
        float oldCr, oldFl;
        moveCamera(oldTime, oldRo, oldTa, oldCr, oldFl);
        mat3 oldCam = setCamera(oldRo, oldTa, oldCr);

        // world space
#if AA>1
        vec3 rd = mul(cam , normalize(vec3(p,fl)));
#endif
        vec3 wpos = ro + rd * t;
        // camera space
        vec3 cpos = vec3(dot(wpos - oldRo, oldCam[0]),
                          dot(wpos - oldRo, oldCam[1]),
                          dot(wpos - oldRo, oldCam[2]));
        // ndc space
        vec2 npos = oldFl * cpos.xy / cpos.z;
        // screen space
        vec2 spos = 0.5 + 0.5 * npos * vec2(iResolution.y / iResolution.x, 1.0);


        // compress velocity vector in a single float
        //vec2 uv = fragCoord / iResolution.xy;
        vec2 uv = fragCoord;
        spos = clamp(0.5 + 0.5 * (spos - uv) / 0.25, 0.0, 1.0);
        vel = floor(spos.x * 255.0) + floor(spos.y * 255.0) * 256.0;
    }
    
    fragColor = vec4(tot, vel);
}

void Elvated(out vec4 fragColor, in vec2 fragCoord)
{
    //vec2 uv = fragCoord / iResolution.xy;
    vec2 uv = fragCoord;
    //vec4 data = texture(iChannel1, uv);
    vec4 data = iChannel0.Sample(splr, uv);

    vec3 col = vec3(0.0, 0.0, 0.0);
    if (data.w < 0.0)
    {
        col = data.xyz;
    }
    else
    {
        // decompress velocity vector
        float ss = mod(data.w, 256.0) / 255.0;
        float st = floor(data.w / 256.0) / 255.0;

        // motion blur (linear blur across velocity vectors
        vec2 dir = (-1.0 + 2.0 * vec2(ss, st)) * 0.25;
        col = vec3(0.0, 0.0, 0.0);
        for (int i = 0; i < 32; i++)
        {
            float h = float(i) / 31.0;
            vec2 pos = uv + dir * h;
            //col += texture(iChannel1, pos).xyz;
            col += iChannel0.Sample(splr, pos).xyz;
        }
        col /= 32.0;
    }
    
    // vignetting	
    col *= 0.5 + 0.5 * pow(16.0 * uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y), 0.1);

    col = clamp(col, 0.0, 1.0);
    col = col * 0.6 + 0.4 * col * col * (3.0 - 2.0 * col) + vec3(0.0, 0.0, 0.04);
    

    
    fragColor = vec4(col, 1.0);
}