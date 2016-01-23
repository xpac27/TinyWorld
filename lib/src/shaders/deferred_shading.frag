#version 330 core

out vec4 frag_coords;
in vec2 text_coords;

uniform sampler2D g_position;
uniform sampler2D g_normal;
uniform sampler2D g_albedo_metallic;

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
vec3 globalIllumination(vec3 reflection, float roughness);
vec3 simpleReinhardToneMapping(vec3 color, float gamma);


// ================================


void main ()
{
    // TODO: Retrieve those info from the app
    float roughness     = 0.15;
    float metallicness  = 0.05;
    // >>>>

// ---- retrieve data from gbuffer

    vec3  fragment_position  = texture(g_position, text_coords).rgb;
    vec3  surface_normal     = texture(g_normal, text_coords).rgb;
    vec3  diffuse_color      = texture(g_albedo_metallic, text_coords).rgb;
    /* float metallicness       = texture(g_albedo_metallic, text_coords).a; */

// ---- pre-compute data

    vec3  view_direction = normalize (view_position - fragment_position);
    vec3  reflection     = reflect(-surface_normal, view_direction);
    float fresnel        = fresnel(surface_normal, view_direction, metallicness);

// ---- direct lighting

    float direct_diffuse_factor  = lambertBRDF(direct_light_direction, surface_normal);
    float direct_specular_factor = cookTorranceBRDF(direct_light_direction, view_direction, surface_normal, roughness, fresnel);
    vec3  direct_specular_color  = direct_specular_factor * direct_light_color;
    vec3  direct_diffuse_color   = direct_diffuse_factor * direct_light_color * (1.0 - fresnel);

// ---- indirect lighting

    vec3 indirect_lighting_color = globalIllumination(reflection, roughness) * direct_light_color;

// ---- combine lighting

    vec3 direct_lighting = max(((direct_diffuse_color + direct_specular_color) * (1.0 - ambiant_color)), vec3(0.0,0.0,0.0));
    vec3 lighting        = direct_lighting + (indirect_lighting_color * ambiant_color) + (fresnel * indirect_lighting_color);

// ---- gamma correction

    vec3 final_color = simpleReinhardToneMapping(diffuse_color * lighting, gamma);

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

