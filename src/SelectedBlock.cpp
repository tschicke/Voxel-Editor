/*
 * SelectedBlock.cpp
 *
 *  Created on: Jun 17, 2013
 *      Author: Tyler
 */

#include "SelectedBlock.h"

#include "Block.h"

SelectedBlock::SelectedBlock() {
	block = NULL;
	x = y = z = 0;
	face = 0;
}

SelectedBlock::SelectedBlock(int x, int y, int z, Block* block, Face face) {
	this->block = block;
	this->x = x;
	this->y = y;
	this->z = z;
	this->face = face;
}

SelectedBlock::~SelectedBlock() {
}

glm::vec3 SelectedBlock::getAddBlockPosition() {
	glm::vec3 addBlockPosition = glm::vec3(x, y, z);
	if(face == face_back){
		addBlockPosition.z -= 1;
	} else if(face == face_front){
		addBlockPosition.z += 1;
	} else if(face == face_left){
		addBlockPosition.x -= 1;
	} else if(face == face_right){
		addBlockPosition.x += 1;
	} else if(face == face_bottom){
		addBlockPosition.y -= 1;
	} else if(face == face_top){
		addBlockPosition.y += 1;
	}

	return addBlockPosition;
}
