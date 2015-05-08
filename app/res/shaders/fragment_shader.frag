#version 410

in vec2 uv;
in vec3 normal;

out vec4 frag_colour;

struct directionalLight
{
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
};

uniform sampler2D textureUnit;
uniform directionalLight light;

void main()
{
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    vec4 diffuseColor;
    float diffuseFactor = dot(normalize(normal), -light.direction);

    if (diffuseFactor > 0) {
        diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;
    } else {
        diffuseColor = vec4(normal, 0.f);
    }

	frag_colour = texture(textureUnit, uv) * (ambientColor + diffuseColor);
}
