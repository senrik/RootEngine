#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	glm::vec3 GetDirection();
	void SetDirection(const glm::vec3*);
	glm::vec3 GetRightAxis();
	glm::vec3 GetUpAxis();
	void UpdateRotation(glm::quat);
	void UpdatePosition(glm::vec3);
	void SetRotation(glm::quat);
	float GetRotationSpeed();
	float GetTranslationSpeed();
private:
	glm::vec3 position, target;
	glm::vec3 direction, rightAxis, upAxis;
	glm::quat rotation;
	float rotationSpeed, translationSpeed;
};

void Camera_Rotate(Camera*, glm::vec3, const float);
void Camera_ResetRotation(Camera*);
void Camera_Translate(Camera*, glm::vec3, const float);
void OrbitCamera_Rotate(Camera*, const float[], const float);

#endif // !CAMERA_H