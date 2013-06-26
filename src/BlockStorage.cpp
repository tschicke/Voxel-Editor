/*
 * ChunkStorage.cpp
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#include "BlockStorage.h"

#include <iostream>

#include "CubeModel.h"

BlockStorage::BlockStorage() {
	init(NULL);
}

BlockStorage::BlockStorage(CubeModel* parentModel) {
	init(parentModel);
}

void BlockStorage::init(CubeModel * parentModel) {
	if (parentModel != NULL) {
		blockArrayLength = parentModel->getWidth() * parentModel->getHeight() * parentModel->getDepth();
		blockArray = new Block *[blockArrayLength];
		for (int i = 0; i < blockArrayLength; ++i) {
			blockArray[i] = NULL;
		}
		parentModelLoaded = true;
	} else {
		parentModelLoaded = false;
	}
	this->parentModel = parentModel;
}

BlockStorage::~BlockStorage() {
	if (parentModelLoaded) {
		for (int i = 0; i < blockArrayLength; ++i) {
			delete blockArray[i];
			blockArray[i] = NULL;
		}

		delete[] blockArray;
		blockArray = NULL;
	}
}

bool BlockStorage::hasParentModel() {
	return parentModelLoaded;
}

int BlockStorage::getBlockArrayLength() {
	return blockArrayLength;
}

Block** BlockStorage::getBlockArray() {
	return blockArray;
}

void BlockStorage::setParentModel(CubeModel* parentModel) {
	if (parentModel != NULL) {
		this->parentModel = parentModel;
		parentModelLoaded = true;
	}
}

void BlockStorage::freeArray() {
	if (parentModelLoaded) {
		for (int i = 0; i < blockArrayLength; ++i) {
			delete blockArray[i];
		}

		delete[] blockArray;
	}
}

void BlockStorage::markBlocksAroundBlockDirty(int x, int y, int z) {
	if(parentModel == NULL){
		return;
	}

	int modelWidth = parentModel->getWidth();
	int modelHeight = parentModel->getHeight();
	int modelDepth = parentModel->getDepth();

	if (x != 0) {
		Block * blockXM1 = blockArray[(x - 1) * modelHeight * modelDepth + y * modelDepth + z];
		if (blockXM1->isDrawn()) {
			blockXM1->setNeedsFaceUpdate(true);
		}
	}
	if (x != modelWidth - 1) {
		Block * blockXP1 = blockArray[(x + 1) * modelHeight * modelDepth + y * modelDepth + z];
		if (blockXP1->isDrawn()) {
			blockXP1->setNeedsFaceUpdate(true);
		}
	}
	if (y != 0) {
		Block * blockYM1 = blockArray[x * modelHeight * modelDepth + (y - 1) * modelDepth + z];
		if (blockYM1->isDrawn()) {
			blockYM1->setNeedsFaceUpdate(true);
		}
	}
	if (y != modelHeight - 1) {
		Block * blockYP1 = blockArray[x * modelHeight * modelDepth + (y + 1) * modelDepth + z];
		if (blockYP1->isDrawn()) {
			blockYP1->setNeedsFaceUpdate(true);
		}
	}
	if (z != 0) {
		Block * blockZM1 = blockArray[x * modelHeight * modelDepth + y * modelDepth + (z - 1)];
		if (blockZM1->isDrawn()) {
			blockZM1->setNeedsFaceUpdate(true);
		}
	}
	if (z != modelDepth - 1) {
		Block * blockZP1 = blockArray[x * modelHeight * modelDepth + y * modelDepth + (z + 1)];
		if (blockZP1->isDrawn()) {
			blockZP1->setNeedsFaceUpdate(true);
		}
	}
}
