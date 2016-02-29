#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gDiffuse;
layout (location = 3) out vec3 gMRS;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec3 Tangent;
in vec3 Bitangent;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_metallic;
uniform sampler2D texture_rough;
uniform sampler2D texture_normal;

void main()
{
	mat3 TBN = mat3(Tangent, Bitangent, Normal);

    // Store the fragment position
    gPosition = FragPos;

    // Store the per-fragment normals
    gNormal.rgb = TBN * normalize(texture(texture_normal, TexCoords).rgb);

    // Store the per-fragment diffuse color
    gDiffuse.rgb = texture(texture_diffuse, TexCoords).rgb;

    // Store the per-fragment metallicness
    gMRS.r = texture(texture_metallic, TexCoords).r;

    // Store the per-fragment roughness
    gMRS.g = texture(texture_rough, TexCoords).r;

    // gMRS.b = ...?
}
