/*
 * CubeModel.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#ifndef CUBEMODEL_H_
#define CUBEMODEL_H_

#include "BlockStorage.h"
#include "ModelRenderer.h"
#include "SelectedBlock.h"

class CubeModel {
public:
	CubeModel();
	CubeModel(int width, int height, int depth);
	virtual ~CubeModel();

	int getWidth();
	int getHeight();
	int getDepth();

	float getScale();

	void update(time_t dt);
	void draw();

	void setColor(glm::vec3 color);

	void save();
	void load();

	SelectedBlock getSelectedBlock();

	friend class ModelRenderer;
private:
	void handleInput();

	int width, height, depth;
	float scale;
	int zoom;

	SelectedBlock selectedBlock;

	glm::vec3 currentColor;

	glm::mat4 viewMatrix;
	bool viewMatrixNeedsUpdate;
	int yaw, pitch;

	BlockStorage * storage;
	ModelRenderer renderer;

	void raytraceBlocks();
};

#endif /* CUBEMODEL_H_ */
