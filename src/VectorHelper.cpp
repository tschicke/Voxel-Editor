/*
 * VectorHelper.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: Tyler
 */

#include "VectorHelper.h"

#include <math.h>

#include <iostream>

const glm::vec3 VectorHelper::NULL_VECTOR = glm::vec3(0, 2056, 0); //Can increase y value or make it negative

glm::vec3 VectorHelper::getIntermediateWithXValue(glm::vec3 v1, glm::vec3 v2, float xVal) {
	float xDiff = v2.x - v1.x;
	float yDiff = v2.y - v1.y;
	float zDiff = v2.z - v1.z;

//	if (xVal == v1.x) {
//		return v1;
//	} else if (xVal == v2.x) {
//		return v2;
//	}

	float xScale = (xVal - v1.x) / xDiff;
	if (xScale > 0 && xScale < 1) {
		return glm::vec3(xVal, v1.y + (yDiff * xScale), v1.z + (zDiff * xScale));
	} else {
		return NULL_VECTOR;
	}
}

glm::vec3 VectorHelper::getIntermediateWithYValue(glm::vec3 v1, glm::vec3 v2, float yVal) {
	float xDiff = v2.x - v1.x;
	float yDiff = v2.y - v1.y;
	float zDiff = v2.z - v1.z;

//	if (yVal == v1.y) {
//		return v1;
//	} else if (yVal == v2.y) {
//		return v2;
//	}

	float yScale = (yVal - v1.y) / yDiff;
	if (yScale > 0 && yScale < 1) {
		return glm::vec3(v1.x + (xDiff * yScale), yVal, v1.z + (zDiff * yScale));
	} else {
		return NULL_VECTOR;
	}
}

glm::vec3 VectorHelper::getIntermediateWithZValue(glm::vec3 v1, glm::vec3 v2, float zVal) {
	float xDiff = v2.x - v1.x;
	float yDiff = v2.y - v1.y;
	float zDiff = v2.z - v1.z;

//	if (zVal == v1.z) {
//		return v1;
//	} else if (zVal == v2.z) {
//		return v2;
//	}

	float zScale = (zVal - v1.z) / zDiff;
	if (zScale > 0 && zScale < 1) {
		return glm::vec3(v1.x + (xDiff * zScale), v1.y + (yDiff * zScale), zVal);
	} else {
		return NULL_VECTOR;
	}
}

bool VectorHelper::isPointInXYBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point) {
//	if (!(v1.z == v2.z && v1.z == point.z)) {
//		return false;
//	}

	int minX = (v1.x < v2.x ? v1.x : v2.x);
	int maxX = (v1.x > v2.x ? v1.x : v2.x);
	int minY = (v1.y < v2.y ? v1.y : v2.y);
	int maxY = (v1.y > v2.y ? v1.y : v2.y);

	return (point.x >= minX && point.x < maxX && point.y >= minY && point.y < maxY);
}

bool VectorHelper::isPointInXZBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point) {
//	if (!(v1.y == v2.y && v1.y == point.y)) {
//		return false;
//	}

	int minX = (v1.x < v2.x ? v1.x : v2.x);
	int maxX = (v1.x > v2.x ? v1.x : v2.x);
	int minZ = (v1.z < v2.z ? v1.z : v2.z);
	int maxZ = (v1.z > v2.z ? v1.z : v2.z);

	return (point.x >= minX && point.x < maxX && point.z >= minZ && point.z < maxZ);
}

bool VectorHelper::isPointInYZBounds(glm::vec3 v1, glm::vec3 v2, glm::vec3 point) {
//	if (!(v1.x == v2.x && v1.x == point.x)) {
//		return false;
//	}

	int minY = (v1.y < v2.y ? v1.y : v2.y);
	int maxY = (v1.y > v2.y ? v1.y : v2.y);
	int minZ = (v1.z < v2.z ? v1.z : v2.z);
	int maxZ = (v1.z > v2.z ? v1.z : v2.z);

	return (point.y >= minY && point.y < maxY && point.z >= minZ && point.z < maxZ);
}
