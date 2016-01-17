#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

struct directionalLight
{
    vec3 color;
    vec3 direction;
};

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
uniform samplerCube environment;
uniform samplerCube irradianceMap;
uniform vec3 view_position;
uniform directionalLight light;

float LambertBRDF ( vec3 lightDirection, vec3 surfaceNormal );
float BeckmannDistribution ( float x, float roughness );
float cookTorranceBRDF ( vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float fresnel );
vec3 RomBinDaHouseToneMapping(vec3 color, float gamma);
vec3 filmicToneMapping(vec3 color);

// ================ MAIN

void main ()
{
    // Setup
    float gamma = 2.2;
    float roughness = 0.85;
    float metallicness = 0.55;

    // Retrieve data from gbuffer
    vec3 fragment_position = texture (gPosition, TexCoords).rgb;
    vec3 surface_normal = texture (gNormal, TexCoords).rgb;
    vec3 diffuse_color = texture (gAlbedoSpec, TexCoords).rgb;
    float specular_intensity = texture (gAlbedoSpec, TexCoords).a;

    // Compute view direction
    vec3 view_direction = normalize (view_position - fragment_position);

    // Directional light
    vec3 light_direction = light.direction * -1;
    /* vec3 light_color = light.color; */
    vec3 light_color = vec3(0.8, 0.8, 0.8);

    // Fresnel
    float NdotV = clamp(dot(surface_normal,view_direction),0.0,1.0);
    NdotV = pow(1.0-NdotV,5.0);
    float Fresnel = metallicness + (1.0-metallicness)*(NdotV);

    // Directional specular
    float specular_factor = cookTorranceBRDF ( light_direction, view_direction, surface_normal, roughness, Fresnel );
    vec3 SpecColor = specular_factor * light_color;

    // Directional diffuse
    float diffuse_factor = LambertBRDF(light_direction, surface_normal);
    vec3 DiffColor = diffuse_color * diffuse_factor * light_color  * (1.0 - Fresnel);

    // Global Illumination
    vec3 R = reflect(view_direction, normalize(surface_normal));
    vec3 R0 = texture(environment, R).rgb;
    vec3 R1 = texture(irradianceMap, R).rgb;
    vec3 global_illumination = mix(R0, R1, roughness);

    // Ambient
    vec3 Ambient = vec3(0.0, 0.0, 0.0);

    // Final color
    vec3 final_color = DiffColor + SpecColor + Ambient + (Fresnel * global_illumination);

    // tone map
    /* final_color = RomBinDaHouseToneMapping(final_color, gamma); */
    /* final_color = filmicToneMapping(final_color); */

    // Gamma correction
    final_color = pow (final_color, vec3 (1.0 / gamma));

    // Output
    FragColor = vec4(final_color, 1.0);
}

// ================================
// https://www.shadertoy.com/view/lslGzl
// ================================

vec3 RomBinDaHouseToneMapping(vec3 color, float gamma)
{
    color = exp( -1.0 / ( 2.72*color + 0.15 ) );
	color = pow(color, vec3(1. / gamma));
	return color;
}

vec3 filmicToneMapping(vec3 color)
{
    color = max(vec3(0.), color - vec3(0.004));
    color = (color * (6.2 * color + .5)) / (color * (6.2 * color + 1.7) + 0.06);
    return color;
}

// ================================
// https://github.com/stackgl
// ================================

float LambertBRDF ( vec3 lightDirection, vec3 surfaceNormal )
{
    return max ( 0.0, dot (lightDirection, surfaceNormal ));
}

float BeckmannDistribution ( float x, float roughness )
{
  float NdotH = max(x, 0.0001);
  float cos2Alpha = NdotH * NdotH;
  float tan2Alpha = (cos2Alpha - 1.0) / cos2Alpha;
  float roughness2 = roughness * roughness;
  float denom = 3.141592653589793 * roughness2 * cos2Alpha * cos2Alpha;
  return exp(tan2Alpha / roughness2) / denom;
}

float cookTorranceBRDF ( vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float fresnel )
{
  float VdotN = max(dot(viewDirection, surfaceNormal), 0.0);
  float LdotN = max(dot(lightDirection, surfaceNormal), 0.0);

  //Half angle vector
  vec3 H = normalize(lightDirection + viewDirection);

  //Geometric term
  float NdotH = max(dot(surfaceNormal, H), 0.0);
  float VdotH = max(dot(viewDirection, H), 0.000001);
  float LdotH = max(dot(lightDirection, H), 0.000001);
  float G1 = (2.0 * NdotH * VdotN) / VdotH;
  float G2 = (2.0 * NdotH * LdotN) / LdotH;
  float G = min(1.0, min(G1, G2));

  //Distribution term
  float D = BeckmannDistribution(NdotH, roughness);

  //Fresnel term (Schlick's Approximation)
  float F = pow(1.0 - VdotN, fresnel);

  //Multiply terms and done
  return  G * F * D / max(3.14159265 * VdotN, 0.000001);
}

