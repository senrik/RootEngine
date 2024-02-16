#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	//glm::vec3 GetDirection();
	//void SetDirection(const glm::vec3*);
	glm::vec3 GetRightAxis();
	glm::vec3 GetUpAxis();
	glm::mat4 GetViewMatrix();
	void UpdateRotation(glm::quat);
	float GetRotationSpeed();
private:
	glm::vec3 position, target;
	glm::vec3 direction, rightAxis, upAxis;
	glm::quat rotation;
	float rotationSpeed;
	// translate camera 
	// - WASD based off of the orientation of the camera
	// rotate camera -- use quaternions
	// - capture the distance the mouse has traveled
	// - rest mouse to center of the screen
	// - store as a unit vector
};

void Camera_Rotate(Camera*, glm::vec3, const float);
void OrbitCamera_Rotate(Camera*, const float[], const float);

#endif // !CAMERA_H