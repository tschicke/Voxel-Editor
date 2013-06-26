/*
 * ModelRenderer.h
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#ifndef ModelRENDERER_H_
#define ModelRENDERER_H_

#include "BaseRenderer.h"
#include "Block.h"

#include "Common.h"
#include <glm/glm.hpp>

class CubeModel;

class ModelRenderer : public BaseRenderer{
public:
	ModelRenderer();
	ModelRenderer(int x, int y, int z, CubeModel * parentModel);
	virtual ~ModelRenderer();

	void init(int x, int y, int z, CubeModel * parentModel);

	void setModelPosition(int x, int y, int z);

	void update(time_t dt);
	void render(glm::mat4 * viewMat);

	void updateBlockFaces(int blockX, int blockY, int blockZ);

	void updateBlockAtPosition(int x, int y, int z);
	void markDirty();

protected:
	bool modelMatNeedsUpdate;

	CubeModel * parentModel;

	glm::vec3 ModelPosition;

	int numVerticesToDraw;

	void remakeIndexBuffer();
	bool needsIndexBufferRemake;
};

#endif /* ModelRENDERER_H_ */
