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
uniform directionalLight light;

uniform vec3 view_position;

void main()
{
    // Retrieve data from gbuffer
    vec3 fragment_position = texture(gPosition, TexCoords).rgb;
    vec3 normal = texture(gNormal, TexCoords).rgb;
    vec3 diffuse_color = texture(gAlbedoSpec, TexCoords).rgb;
    float specular_intensity = texture(gAlbedoSpec, TexCoords).a;

    // Setup
    float gamma = 2.2;
    vec3 view_direction = normalize(view_position - fragment_position);

    // Directional light
    vec3 lighting = vec3(0.0, 0.0, 0.0); // no ambiant color
    vec3 light_direction = light.direction * -1;
    vec3 light_color = light.color;

    // Directional diffuse
    float diffuse_intensity = max(dot(light_direction, normal), 0.0);
    lighting += diffuse_color * diffuse_intensity * light_color;

    // Directional specular
    vec3 halfway = normalize(light_direction + view_direction);
    float specular_reflection = pow(max(dot(normal, halfway), 0.0), 32.0) / 2.0;
    lighting += specular_intensity * specular_reflection;

    // For each spot lights (TODO)
    // {
    // }

    // apply gamma correction
    lighting = pow(lighting, vec3(1.0/gamma));

    // Output result
    FragColor = vec4(lighting, 1.0);
}
