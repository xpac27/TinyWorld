#version 330

out float fragmentdepth;

void main()
{
    fragmentdepth = gl_FragCoord.z;
}
