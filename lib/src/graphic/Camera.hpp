#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera
{

public:

	Camera(float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z);

	const glm::vec3& getPosition() const;
	const glm::mat4& getPerspective() const;
	const glm::mat4& getTranslation() const;
	const glm::mat4& getRotation() const;

private:

	glm::vec3 position;
	glm::mat4 perspective;
	glm::mat4 translation;
	glm::mat4 rotation;
};
