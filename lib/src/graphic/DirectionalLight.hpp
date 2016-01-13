#pragma once
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct DirectionalLight
{
    glm::vec3 color;
    glm::vec4 direction;

    DirectionalLight() {}
    DirectionalLight(glm::vec3 _color, glm::vec4 _direction)
        : color(_color)
        , direction(_direction)
    {}
};
