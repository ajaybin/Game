#ifndef MATHS_H
#define MATHS_H
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Maths {
public:
	static glm::mat4 createModelMatrix(glm::vec3 translation, float angleX, float angleY, float angleZ, glm::vec3 scale);
	static glm::mat4 createProjectionMatrix(float fov, float aspectRatio, float near, float far);
	static glm::mat4 createViewMatrix(glm::vec3 position);
};
#endif
