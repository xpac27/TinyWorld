#pragma once
#include <glm/vec3.hpp>

struct DirectionalLight
{
    glm::vec3 color;
    glm::vec3 direction;

    float ambientIntensity;
    float diffuseIntensity;
    float intensity;

    DirectionalLight() {}
    DirectionalLight(glm::vec3 _color, glm::vec3 _direction, float _ambientIntensity, float _diffuseIntensity, float _intensity)
        : color(_color)
        , direction(_direction)
        , ambientIntensity(_ambientIntensity)
        , diffuseIntensity(_diffuseIntensity)
        , intensity(_intensity)
    {}
};
