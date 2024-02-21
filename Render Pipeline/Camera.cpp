#include "Camera.hpp"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, -1.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(target - position);
	upAxis = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
	rotationSpeed = 5.0f;
	translationSpeed = 2.0f;
}

glm::vec3 Camera::GetUpAxis() {
	return upAxis;

}

float Camera::GetRotationSpeed() {
	return rotationSpeed;
}

float Camera::GetTranslationSpeed() {
	return translationSpeed;
}

void Camera::UpdateRotation(glm::quat _newRot) {
	rotation = rotation * _newRot;

	upAxis = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

void Camera::SetRotation(glm::quat _rot) {
	rotation = _rot;
	upAxis = rotation * glm::vec3(0.0f, 1.0f, 0.0f);
	rightAxis = rotation * glm::vec3(1.0f, 0.0f, 0.0f);
}

void Camera::UpdatePosition(glm::vec3 _vec) {
	//position += rotation *_vec;
	//target += rotation* _vec;
}

void Camera_Update(Camera* _cam) {
}

void Camera_ResetRotation(Camera* _cam) {
	_cam->SetRotation(glm::quat());
}

void Camera_Translate(Camera* _cam, glm::vec3 _axis, const float deltaTime) {
	_cam->UpdatePosition(glm::normalize(_axis) * deltaTime * _cam->GetTranslationSpeed());
}

void Camera_Rotate(Camera* _cam, glm::vec3 _eulerVec, const float deltaTime) {
	_cam->UpdateRotation(glm::quat(glm::normalize(_eulerVec) * _cam->GetRotationSpeed()));
}