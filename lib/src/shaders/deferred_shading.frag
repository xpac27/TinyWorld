#version 330 core

out vec4 frag_coords;
in vec2 text_coords;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_diffuse;
uniform sampler2D g_mr;
uniform sampler2D g_shadow;

uniform samplerCube environment;
uniform samplerCube irradiance_map;

uniform vec3 view_position;
uniform vec3 ambiant_color;
uniform vec3 direct_light_color;
uniform vec3 direct_light_direction;

uniform float gamma;

float fresnel(vec3 light_direction, vec3 view_direction, float metallicness);
float lambertBRDF(vec3 light_direction, vec3 surface_normal);
float beckmannDistribution(float x, float roughness);
float cookTorranceBRDF(vec3 light_direction, vec3 view_direction, vec3 surface_normal, float roughness, float fresnel);
vec3 hsv2rgb(in vec3 c);
vec3 rgb2hsv(vec3 c);
vec3 artisticShading(vec3 diffuse_color, vec3 light_direction, vec3 surface_normal);
vec3 globalIllumination(vec3 reflection, float roughness);
vec3 simpleReinhardToneMapping(vec3 color, float gamma);


// ================================


void main ()
{

// ---- retrieve data from gbuffer

    vec3  fragment_position = texture(g_position, text_coords).rgb;
    vec3  surface_normal    = texture(g_normal, text_coords).rgb;
    vec3  diffuse           = texture(g_diffuse, text_coords).rgb;
    float metallicness      = texture(g_mr, text_coords).r;
    float roughness         = max(texture(g_mr, text_coords).g, 0.0001);
    float shadow            = texture(g_shadow, text_coords).r;

// ---- pre-compute data

    vec3  view_direction = normalize (view_position - fragment_position);
    vec3  reflection     = reflect(-surface_normal, view_direction);
    float fresnel        = fresnel(surface_normal, view_direction, metallicness);
    float drop_shadow    = 1. + (1. - (shadow - fresnel));

// ---- direct lighting

    float direct_diffuse_factor  = lambertBRDF(direct_light_direction, surface_normal);
    float direct_specular_factor = cookTorranceBRDF(direct_light_direction, view_direction, surface_normal, roughness, fresnel);
    vec3  direct_specular_color  = direct_specular_factor * direct_light_color;
    vec3  direct_diffuse_color   = direct_diffuse_factor * direct_light_color * (1.0 - fresnel);
    vec3  direct_lighting        = direct_diffuse_color + direct_specular_color;

// ---- indirect lighting

    vec3 indirect_lighting = globalIllumination(reflection, roughness) * direct_light_color * fresnel;

// ---- combine lighting

    vec3 lighting = direct_lighting + indirect_lighting;

// ---- Artistic shading

    vec3 diffuse_color = artisticShading(diffuse, direct_light_direction, surface_normal);

// ---- gamma correction

    vec3 final_color = simpleReinhardToneMapping(diffuse_color * lighting / drop_shadow, gamma);

// ---- output

    frag_coords = vec4(final_color, 1.0);
}

// ================================

float fresnel(vec3 surface_normal, vec3 view_direction, float metallicness)
{
    float NdotV = pow(1.0 - clamp(dot(surface_normal, view_direction), 0.0, 1.0), 5.0);
    return metallicness + ((1.0 - metallicness) * NdotV);
}

vec3 globalIllumination(vec3 reflection, float roughness)
{
    vec3 R0 = texture(environment, reflection).rgb;
    vec3 R1 = texture(irradiance_map, reflection).rgb;
    return mix(R0, R1, roughness);
}

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

// ================================
// https://www.shadertoy.com/view/Xtj3Dm
// ================================

vec3 artisticShading(vec3 diffuse_color, vec3 light_direction, vec3 surface_normal)
{
    vec3  hsv = rgb2hsv(diffuse_color);
    float nl = clamp(dot(surface_normal, direct_light_direction), 0., 1.);
    float vari = sin(nl * 6.28 * 0.5 - 1.5708);
    hsv.x += (nl - 0.7) * 0.08; //Hue variation
    hsv.y += vari * 0.1;        //Saturation variation
    hsv.z += vari * 0.12 * nl;  //Value variation
    /* hsv.z += sin(nl * 6.28 * 1. + 3.14159) * 0.13; //Can be higher freqency */
    return hsv2rgb(hsv);
}

// ================================
// https://www.shadertoy.com/view/lslGzl
// ================================

vec3 simpleReinhardToneMapping(vec3 color, float gamma)
{
    float exposure = 1.5;
    color *= exposure/(1. + color / exposure);
    color = pow(color, vec3(1. / gamma));
    return color;
}

// ================================
// https://github.com/stackgl
// ================================

float lambertBRDF ( vec3 light_direction, vec3 surface_normal )
{
    return max ( 0.0, dot (light_direction, surface_normal ));
}

float beckmannDistribution ( float x, float roughness )
{
  float NdotH = max(x, 0.0001);
  float cos2Alpha = NdotH * NdotH;
  float tan2Alpha = (cos2Alpha - 1.0) / cos2Alpha;
  float roughness2 = roughness * roughness;
  float denom = 3.141592653589793 * roughness2 * cos2Alpha * cos2Alpha;
  return exp(tan2Alpha / roughness2) / denom;
}

float cookTorranceBRDF ( vec3 light_direction, vec3 view_direction, vec3 surface_normal, float roughness, float fresnel )
{
  float VdotN = max(dot(view_direction, surface_normal), 0.0);
  float LdotN = max(dot(light_direction, surface_normal), 0.0);

  //Half angle vector
  vec3 H = normalize(light_direction + view_direction);

  //Geometric term
  float NdotH = max(dot(surface_normal, H), 0.0);
  float VdotH = max(dot(view_direction, H), 0.000001);
  float LdotH = max(dot(light_direction, H), 0.000001);
  float G1 = (2.0 * NdotH * VdotN) / VdotH;
  float G2 = (2.0 * NdotH * LdotN) / LdotH;
  float G = min(1.0, min(G1, G2));

  //Distribution term
  float D = beckmannDistribution(NdotH, roughness);

  //Fresnel term (Schlick's Approximation)
  float F = pow(1.0 - VdotN, fresnel);

  //Multiply terms and done
  return  G * F * D / max(3.14159265 * VdotN, 0.000001);
}

