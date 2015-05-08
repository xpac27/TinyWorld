#version 410

in vec2 uv;
out vec4 frag_colour;

struct directionalLight
{
    vec3 color;
    float ambientIntensity;
};

uniform sampler2D textureUnit;
uniform directionalLight light;

void main()
{
	frag_colour = texture(textureUnit, uv) * vec4(light.color, 1.0f) * light.ambientIntensity;
}
