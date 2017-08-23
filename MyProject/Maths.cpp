#include "Maths.h"

glm::mat4 Maths::createModelMatrix(glm::vec3 translation, float angleX, float angleY, float angleZ, glm::vec3 scale)
{
	glm::mat4 modelMat = glm::mat4(1);
	modelMat = glm::translate(modelMat, translation);
	modelMat = glm::rotate(modelMat, angleX, glm::vec3(1.0, 0.0, 0.0));
	modelMat = glm::rotate(modelMat, angleY, glm::vec3(0.0, 1.0, 0.0));
	modelMat = glm::rotate(modelMat, angleZ, glm::vec3(0.0, 0.0, 1.0));
	modelMat = glm::scale(modelMat, scale);
	return modelMat;
}

glm::mat4 Maths::createProjectionMatrix(float fov, float aspectRatio, float near, float far) {
#ifdef GLM_FORCE_RADIANS
	return glm::perspective(glm::radians(fov), aspectRatio, near, far);
#else
	return glm::perspective(fov, aspectRatio, near, far);
#endif

}
