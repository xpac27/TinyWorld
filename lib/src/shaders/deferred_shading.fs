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
uniform vec3 view_position;
uniform directionalLight light;

float LambertBRDF ( vec3 lightDirection, vec3 surfaceNormal );
float BeckmannDistribution ( float x, float roughness );
float cookTorranceBRDF ( vec3 lightDirection, vec3 viewDirection, vec3 surfaceNormal, float roughness, float fresnel );


// ================ MAIN

void main ()
{
    /*
    // Retrieve data from gbuffer
    vec3 fragment_position = texture (gPosition, TexCoords).rgb;
    vec3 surface_normal = texture (gNormal, TexCoords).rgb;
    vec3 diffuse_color = texture (gAlbedoSpec, TexCoords).rgb;
    float specular_intensity = texture (gAlbedoSpec, TexCoords).a;

    // Setup
    float gamma = 2.2;
    vec3 view_direction = normalize (view_position - fragment_position);

    // Directional light
    vec3 lighting = vec3 (0.0, 0.0, 0.0); // no ambiant color
    vec3 light_direction = light.direction * -1;
    vec3 light_color = light.color;

    // Directional diffuse
    lighting += diffuse_color * light_color * lambertDiffuse(light_direction, surface_normal);

    // Directional specular
    // vec3 halfway = normalize (light_direction + view_direction);
    // float specular_reflection = pow (max (dot (surface_normal, halfway), 0.0), 32.0) / 2.0;
    // lighting += specular_intensity * specular_reflection;

    // For each spot lights  (TODO)
    // {
    // }

    // apply gamma correction
    lighting = pow (lighting, vec3 (1.0 / gamma));

    // Output result
    // FragColor = vec4 (specular_intensity, specular_intensity, specular_intensity, 1.0);
    // FragColor = vec4 (diffuse_intensity, diffuse_intensity, diffuse_intensity, 1.0);
    // FragColor = vec4 (diffuse_color, 1.0);
    // FragColor = vec4 (surface_normal, 1.0);
    // FragColor = vec4 (fragment_position, 1.0);
    FragColor = vec4 (lighting, 1.0);
    */

    // Settings
    float gamma = 2.2;
    float roughness = 0.30;
    float fresnel = 0.2;

    // Temporary
    vec3 specular_color = vec3 (1.0, 1.0, 1.0);

    // Extract information from prerendered texture
    vec3 base_color = texture (gAlbedoSpec, TexCoords).rgb;
    vec3 surface_normal = texture (gNormal, TexCoords).rgb;
    vec3 fragment_position = texture (gPosition, TexCoords).rgb;

    // Compute directions
    vec3 view_direction = normalize (view_position - fragment_position);
    vec3 light_direction = light.direction * -1;

    // Compute lighting
    float diffuse_factor = LambertBRDF(light_direction, surface_normal);
    float specular_factor = cookTorranceBRDF ( light_direction, view_direction, surface_normal, roughness, fresnel );
    vec3 lighting = base_color * diffuse_factor + specular_color * specular_factor;

    // apply gamma correction
    lighting = pow (lighting, vec3 (1.0 / gamma));

    FragColor = vec4 (lighting, 1.0);
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

  //Fresnel term
  float F = pow(1.0 - VdotN, fresnel);

  //Multiply terms and done
  return  G * F * D / max(3.14159265 * VdotN, 0.000001);
}

