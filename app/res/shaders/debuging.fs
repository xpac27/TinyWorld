#version 330

in vec2 uv0;

out vec4 frag_colour;

uniform sampler2D textureUnit;

void main()
{
    frag_colour = texture(textureUnit, uv0);
}
