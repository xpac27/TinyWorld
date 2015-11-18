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

    // Directional light
    float visibility = dot(Normal, -Light.direction);
    if (visibility > 0.0) {

        // Diffuse
        vec3 diffuse = Diffuse * Light.color * pow(visibility, 2);
        lighting += diffuse;

        // Specular
        float reflection = dot(Normal, normalize(-Light.direction + viewDir));
        if (reflection > 0.0) {
            lighting += Specular * Light.color * pow(reflection, 32);
        }
    }

    // For each spot lights (TODO)
    // {
    // }

    FragColor = vec4(lighting, 1.0);
}
