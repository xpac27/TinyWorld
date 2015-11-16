#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

struct directionalLight
{
    vec3 color;
    vec3 direction;
    float intensity;
};
uniform directionalLight Light;

uniform vec3 viewPos;

void main()
{
    // Retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;

    // Setup
    vec3 viewDir = normalize(viewPos - FragPos);

    // Hard-coded ambient component
    vec3 lighting = Diffuse * 0.1;

    // Directional light
    // <<
        // Diffuse
        vec3 diffuse = max(dot(Normal, -Light.direction), 0.0) * Light.intensity * Light.color * Diffuse;
        // Specular
        vec3 reflectDir = reflect(-Light.direction, Normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = Light.color * spec * Specular;
        // Compute
        lighting += diffuse + specular;
    // >>

    // For each spot lights (TODO)
    // {
    // }

    FragColor = vec4(lighting, 1.0);
}
