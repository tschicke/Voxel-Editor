/*
 * Block.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include <glm/glm.hpp>

#include "SelectedBlock.h"

class Block {
public:
	Block();
	Block(float r, float g, float b, bool drawn);
	virtual ~Block();

	void setNeedsFaceUpdate(bool b);

	bool isDrawn();
	void setDrawn(bool drawn);

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	glm::vec3 getColor();

	Face raytrace(int x, int y, int z, glm::vec3 startVec, glm::vec3 endVec);
private:
	bool needsFaceUpdate;
	bool drawn;

	glm::vec3 color;
};

#endif /* BLOCK_H_ */
