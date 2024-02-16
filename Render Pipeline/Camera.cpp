#include "Camera.hpp"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, -5.0f);
	target = glm::vec3(0.0f);
	
	direction = glm::normalize(target - position);
	upAxis = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	rotationSpeed = 5.0f;

}

float Camera::GetRotationSpeed() {
	return rotationSpeed;
}

void Camera::UpdateRotation(glm::quat _newRot) {
	rotation = _newRot* rotation ;
}

void Camera_Rotate(Camera* _cam, glm::vec3 _axis, const float deltaTime) {
	_cam->UpdateRotation(glm::quat(glm::normalize(_axis) * deltaTime * _cam->GetRotationSpeed()));
}

glm::mat4 Camera::GetViewMatrix() {
	
	return glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation);
}