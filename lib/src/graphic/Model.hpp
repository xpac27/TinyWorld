#pragma once
#include <glm/mat4x4.hpp>

class Model
{

public:

    Model(glm::mat4 _translation, glm::mat4 _rotation, glm::mat4 _scale);

    const glm::mat4& getTranslation() const;
    const glm::mat4& getRotation() const;
    const glm::mat4& getScale() const;
    const glm::mat4& getProduct() const;

private:

    glm::mat4 translation;
    glm::mat4 rotation;
    glm::mat4 scale;
    glm::mat4 product;
};
