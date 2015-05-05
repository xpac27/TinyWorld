#version 410

in vec2 uv_0;

uniform sampler2D sampler;

out vec4 frag_colour;

void main()
{
	frag_colour = texture(sampler, uv_0.st);
}
