#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera::Camera(float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z)
    : position(pos_x, pos_y, pos_z)
	, perspective(glm::infinitePerspective(float(M_PI) / 2.f, 4.f / 3.f, 0.1f))
	, translation(translate(mat4(1.0f), vec3(pos_x, pos_y, pos_z) * -1.f))
    , rotation(mat4(1.0f))
{
    rotation = rotate(rotation, rot_x, vec3(1.0f, 0.0f, 0.0f));
    rotation = rotate(rotation, rot_y, vec3(0.0f, 0.0f, 1.0f));
    rotation = rotate(rotation, rot_z, vec3(0.0f, 0.0f, 1.0f));

}

const vec3& Camera::getPosition() const
{
	return position;
}

const mat4& Camera::getPerspective() const
{
	return perspective;
}

const mat4& Camera::getTranslation() const
{
	return translation;
}

const mat4& Camera::getRotation() const
{
	return rotation;
}
