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
uniform sampler2D BRDFIntegrationMap;
uniform vec3 view_position;
uniform directionalLight light;

float LambertBRDF ( vec3 lightDirection, vec3 surfaceNormal );
float BeckmannDistribution ( float x, float roughness );
float cookTorranceBRDF ( vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float fresnel );
vec3 linearToneMapping(vec3 color, float gamma);
vec3 simpleReinhardToneMapping(vec3 color, float gamma);
vec3 whitePreservingLumaBasedReinhardToneMapping(vec3 color, float gamma);

// ================ MAIN

void main ()
{
    // Setup
    float gamma = 2.2;
    float roughness = 0.05;
    float metallicness = 0.99;

    // Retrieve data from gbuffer
    vec3 fragment_position = texture(gPosition, TexCoords).rgb;
    vec3 surface_normal = texture(gNormal, TexCoords).rgb;
    vec3 diffuse_color = texture(gAlbedoSpec, TexCoords).rgb;
    float specular_intensity = texture(gAlbedoSpec, TexCoords).a;

    // Compute view direction
    vec3 view_direction = normalize (view_position - fragment_position);

    // Directional light
    vec3 light_direction = light.direction * -1.0;
    vec3 specular_color = light.color;

    // Reflection
    vec3 reflection = reflect(view_direction, normalize(surface_normal));

    // Fresnel
    float NdotV = pow(1.0 - clamp(dot(surface_normal, view_direction), 0.0, 1.0), 5.0);
    float fresnel = metallicness + ((1.0 - metallicness) * NdotV);

    // Direct lighting
    float direct_diffuse_factor = LambertBRDF(light_direction, surface_normal);
    float direct_specular_factor = cookTorranceBRDF(light_direction, view_direction, surface_normal, roughness, fresnel);
    vec3 direct_lighting = (diffuse_color * direct_diffuse_factor) + (specular_color * direct_specular_factor * specular_intensity);

    // Indirect lighting
    vec3 R0 = texture(environment, reflection).rgb;
    vec3 R1 = texture(irradianceMap, reflection).rgb;
    vec2 envBRDF = texture(BRDFIntegrationMap, vec2(roughness, NdotV)).xy;
    vec3 indirect_lighting = (R1 + mix(R0, R1, roughness) * (specular_color * envBRDF.x + envBRDF.y) * fresnel);

    // Combine lighting
    vec3 color = (direct_lighting + indirect_lighting) * direct_diffuse_factor;

    // Gamma correction
    /* vec3 final_color = linearToneMapping(color, gamma); */
    vec3 final_color = simpleReinhardToneMapping(color, gamma);
    /* vec3 final_color = whitePreservingLumaBasedReinhardToneMapping(color, gamma); */

    // Output
    FragColor = vec4(final_color, 1.0);
}

// ================================
// https://www.shadertoy.com/view/lslGzl
// ================================

vec3 linearToneMapping(vec3 color, float gamma)
{
	float exposure = 1.;
	color = clamp(exposure * color, 0., 1.);
	color = pow(color, vec3(1. / gamma));
	return color;
}

vec3 simpleReinhardToneMapping(vec3 color, float gamma)
{
	float exposure = 1.5;
	color *= exposure/(1. + color / exposure);
	color = pow(color, vec3(1. / gamma));
	return color;
}

vec3 whitePreservingLumaBasedReinhardToneMapping(vec3 color, float gamma)
{
	float white = 2.;
	float luma = dot(color, vec3(0.2126, 0.7152, 0.0722));
	float toneMappedLuma = luma * (1. + luma / (white*white)) / (1. + luma);
	color *= toneMappedLuma / luma;
	color = pow(color, vec3(1. / gamma));
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

