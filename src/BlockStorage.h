/*
 * ChunkStorage.h
 *
 *  Created on: May 11, 2013
 *      Author: Tyler
 */

#ifndef BLOCKSTORAGE_H_
#define BLOCKSTORAGE_H_

#include "Block.h"

class CubeModel;

class BlockStorage {
public:
	BlockStorage();
	BlockStorage(CubeModel * parentModel);
	virtual ~BlockStorage();

	void setParentModel(CubeModel * parentModel);

	bool hasParentModel();
	int getBlockArrayLength();
	Block** getBlockArray();

	void freeArray();

	void markBlocksAroundBlockDirty(int x, int y, int z);
private:
	BlockStorage(const BlockStorage& copy);
	BlockStorage& operator=(const BlockStorage& copy);

	Block ** blockArray;
	int blockArrayLength;

	void init(CubeModel * parentModel);

	bool parentModelLoaded;

	CubeModel * parentModel;
};

#endif /* BLOCKSTORAGE_H_ */
