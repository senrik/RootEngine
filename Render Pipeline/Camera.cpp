#include "Camera.hpp"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, -1.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(target - position);
	// global up
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = glm::normalize(glm::cross(up, direction));
	upAxis = glm::normalize(glm::cross(direction, rightAxis));
	rotationSpeed = 30.0f;
};

void Camera::SetDirection(const glm::vec3* _dir) {
	direction = *_dir;
}

glm::vec3 Camera::GetUpAxis() {
	return upAxis;
}

glm::vec3 Camera::GetRightAxis() {
	return rightAxis;
}

void Camera_Update(Camera* _cam) {
}

// update the direction _dir[0] is the rotation around the x axis _dir[1] is the rotation around the y axis
void OrbitCamera_Rotate(Camera* _cam, const float _dir[], const float deltaTime) {
	// the rotation will move the camera to a new location
	_cam->position = glm::vec3(0.0f, 0.0f, 0.0f);
	// rotate the camera around the global y-axis (up)
	
	// rotate the cmaera around its own right axis
}