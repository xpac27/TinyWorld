#include "../../inc/graphic/Model.hpp"

using namespace glm;

Model::Model(mat4 _translation, mat4 _rotation, mat4 _scale)
    : translation(_translation)
    , rotation(_rotation)
    , scale(_scale)
    , product(_translation * _rotation * _scale)
{}

const glm::mat4& Model::getTranslation() const
{
    return translation;
}

const glm::mat4& Model::getRotation() const
{
    return rotation;
}

const glm::mat4& Model::getScale() const
{
    return scale;
}

const glm::mat4& Model::getProduct() const
{
    return product;
}
