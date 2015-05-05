#version 410

uniform sampler2D textureUnit;

in vec2 uv;
out vec4 frag_colour;

void main()
{
	frag_colour = texture(textureUnit, uv);
}
