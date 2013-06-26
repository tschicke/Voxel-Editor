/*
 * VectorHelper.h
 *
 *  Created on: Jun 15, 2013
 *      Author: Tyler
 */

#ifndef VECTORHELPER_H_
#define VECTORHELPER_H_

#include <glm/glm.hpp>

class VectorHelper {
public:
	static const glm::vec3 NULL_VECTOR;

	static glm::vec3 getIntermediateWithXValue(glm::vec3 v1, glm::vec3 v2, float xVal);
	static glm::vec3 getIntermediateWithYValue(glm::vec3 v1, glm::vec3 v2, float yVal);
	static glm::vec3 getIntermediateWithZValue(glm::vec3 v1, glm::vec3 v2, float zVal);

	static bool isPointInXYBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point);
	static bool isPointInXZBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point);
	static bool isPointInYZBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point);
};

#endif /* VECTORHELPER_H_ */
