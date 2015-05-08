#version 410

in vec2 uv0;
in vec3 normal0;
in vec3 worldPosition0;

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

uniform vec3 eyeWorldPositon;
uniform float specularIntensity;
uniform float specularPower;

void main()
{
    vec4 diffuseColor = vec4(0, 0, 0, 0);
    vec4 specularColor = vec4(0, 0, 0, 0);
    vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
    vec3 lightDirection = -light.direction;
    vec3 normal = normalize(normal0);
    float diffuseFactor = dot(normal, -light.direction);

    if (diffuseFactor > 0) {
        diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;


        vec3 vertexToEye = normalize(eyeWorldPositon - worldPosition0);
        vec3 lightReflect = normalize(reflect(light.direction, normal));
        float specularFactor = dot(vertexToEye, lightReflect);
        specularFactor = pow(specularFactor, specularPower);
        if (specularFactor > 0) {
            specularColor = vec4(light.color, 1.0f) * specularIntensity * specularFactor;
        }
    }

	frag_colour = texture(textureUnit, uv0) * (ambientColor + diffuseColor + specularColor);
}
