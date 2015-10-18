#version 330

in vec2 uv0;

out vec4 frag_colour;

uniform sampler2D textureUnit;

void main()
{
    float depth = texture(textureUnit, uv0).x;
    depth = 1.0 - (1.0 - depth) * 25.0;
    frag_colour = vec4(depth);
}
