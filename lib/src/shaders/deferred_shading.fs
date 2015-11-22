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
    vec3 lighting = vec3(0.0, 0.0, 0.0);
    vec3 lightDir = Light.direction * -1;
    float gamma = 2.2;

    // Directional light
    float intensity = dot(lightDir, Normal);
    if (intensity > 0.0) {

        // Diffuse
        vec3 diffuse = Diffuse * Light.color * intensity;
        lighting += diffuse;

        // Specular
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(Normal, halfwayDir), 0.0), 32.0) / 2.0;
        lighting += Specular * Light.color * spec * intensity;
    }

    // For each spot lights (TODO)
    // {
    // }

    // apply gamma correction
    lighting = pow(lighting, vec3(1.0/gamma));

    // Output result
    FragColor = vec4(lighting, 1.0);
}
