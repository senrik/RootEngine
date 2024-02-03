#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera {
	Camera();
	// pos -- vec3
	// direction -- quaternion?
	// target -- vec3
	// right axis -- vec3
	// up axis -- vec3
	// translate camera 
	// - WASD based off of the orientation of the camera
	// rotate camera -- use quaternions
	// - capture the distance the mouse has traveled
	// - rest mouse to center of the screen
	// - store as a unit vector
};

#endif // !CAMERA_H


