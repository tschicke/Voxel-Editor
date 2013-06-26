/*
 * SelectedBlock.h
 *
 *  Created on: Jun 17, 2013
 *      Author: Tyler
 */

#ifndef SELECTEDBLOCK_H_
#define SELECTEDBLOCK_H_

#include <glm/glm.hpp>

class Block;

enum Face{
	face_back, face_front, face_left, face_right, face_bottom, face_top, face_nocollision
};

class SelectedBlock {
public:
	SelectedBlock();
	SelectedBlock(int x, int y, int z, Block * block, Face face);
	virtual ~SelectedBlock();

	int x, y, z;
	Block * block;

	int face;

	glm::vec3 getAddBlockPosition();
};

#endif /* SELECTEDBLOCK_H_ */
