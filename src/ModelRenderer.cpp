/*
 * ModelRenderer.cpp
 *
 *  Created on: May 19, 2013
 *      Author: Tyler
 */

#include <iostream>
#include <fstream>

#include "ModelRenderer.h"

#include "CubeModel.h"

#include <gl/glew.h>

#include <glm/gtx/transform.hpp>

#include <vector>

ModelRenderer::ModelRenderer() {
	modelMatNeedsUpdate = false;
	parentModel = NULL;
	numVerticesToDraw = 0;
	needsIndexBufferRemake = false;
}

ModelRenderer::ModelRenderer(int x, int y, int z, CubeModel * parentModel) {
	init(x, y, z, parentModel);
}

void ModelRenderer::init(int x, int y, int z, CubeModel * parentModel) {
	if (parentModel == NULL) {
		*this = ModelRenderer();
		return;
	}

	this->parentModel = parentModel;

	Shader vertexShader;
	vertexShader.loadShader("shaders/colorShader.vert", GL_VERTEX_SHADER);

	Shader fragmentShader;
	fragmentShader.loadShader("shaders/colorShader.frag", GL_FRAGMENT_SHADER);

	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&fragmentShader);
	shaderProgram.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	ModelPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;

	int modelWidth = parentModel->getWidth();
	int modelHeight = parentModel->getHeight();
	int modelDepth = parentModel->getDepth();

	int numCubes = modelWidth * modelHeight * modelDepth;

	int numVerticesPerModel = numCubes * 24 * 3;
	int numColorsPerModel = numCubes * 24 * 3;
	int numNormalsPerModel = numCubes * 24 * 3;
	int numIndicesPerModel = numCubes * 36;

	initBuffersWithSize((numVerticesPerModel + numColorsPerModel + numNormalsPerModel) * sizeof(float), numIndicesPerModel * sizeof(unsigned int));

	float * vertexArray = new float[numVerticesPerModel + numColorsPerModel + numNormalsPerModel];

	/*   Cube Diagram
	 *
	 * 		  p7__________p6
	 * 		   /|		 /|
	 * 		p3/_|_____p2/ |
	 * 		 |  |	   |  |
	 * 		 |	|p4____|__|p5
	 * 		 | /	   | /
	 * 	   p0|/________|/p1
	 */

	float cubeSize = parentModel->getScale();

	float cubeVertexData[] = {
			//Front
			0, 0, cubeSize,
			cubeSize, 0, cubeSize,
			cubeSize, cubeSize, cubeSize,
			0, cubeSize, cubeSize,

			//Back
			cubeSize, 0, 0,
			0, 0, 0,
			0, cubeSize, 0,
			cubeSize, cubeSize, 0,

			//Left
			0, 0, 0,
			0, 0, cubeSize,
			0, cubeSize, cubeSize,
			0, cubeSize, 0,

			//Right
			cubeSize, 0, cubeSize,
			cubeSize, 0, 0,
			cubeSize, cubeSize, 0,
			cubeSize, cubeSize, cubeSize,

			//Top
			0, cubeSize, cubeSize,
			cubeSize, cubeSize, cubeSize,
			cubeSize, cubeSize, 0,
			0, cubeSize, 0,

			//Bottom
			0, 0, 0,
			cubeSize, 0, 0,
			cubeSize, 0, cubeSize,
			0, 0, cubeSize
	};

	float cubeNormalData[] = {
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,

			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,

			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0
	};

	Block ** blockArray = parentModel->storage->getBlockArray();

	for (int x = 0; x < modelWidth; ++x) {
		for (int y = 0; y < modelHeight; ++y) {
			for (int z = 0; z < modelDepth; ++z) {
				int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;

				int numVerticesPerCube = 24;

				int vertexIndex = blockIndex * numVerticesPerCube * 3;
				int colorIndex = blockIndex * numVerticesPerCube * 3;
				int normalIndex = blockIndex * numVerticesPerCube * 3;

				Block * block = blockArray[blockIndex];

				if (block != NULL && block->isDrawn()) {
					for (int i = 0; i < numVerticesPerCube; ++i) {
						vertexArray[vertexIndex + (i * 3)] = cubeVertexData[(i * 3)] + x;
						vertexArray[vertexIndex + (i * 3) + 1] = cubeVertexData[(i * 3) + 1] + y;
						vertexArray[vertexIndex + (i * 3) + 2] = cubeVertexData[(i * 3) + 2] + z;

						vertexArray[numVerticesPerModel + colorIndex + (i * 3)] = block->getColor().r;
						vertexArray[numVerticesPerModel + colorIndex + (i * 3) + 1] = block->getColor().g;
						vertexArray[numVerticesPerModel + colorIndex + (i * 3) + 2] = block->getColor().b;

						vertexArray[numVerticesPerModel + numColorsPerModel + normalIndex + (i * 3)] = cubeNormalData[(i * 3)];
						vertexArray[numVerticesPerModel + numColorsPerModel + normalIndex + (i * 3) + 1] = cubeNormalData[(i * 3) + 1];
						vertexArray[numVerticesPerModel + numColorsPerModel + normalIndex + (i * 3) + 2] = cubeNormalData[(i * 3) + 2];
					}
				}
			}
		}
	}

	substituteDataToVertexBuffer((numVerticesPerModel + numColorsPerModel + numNormalsPerModel) * sizeof(float), 0, vertexArray);

	remakeIndexBuffer();

	delete[] vertexArray;
}

ModelRenderer::~ModelRenderer() {
//	deleteBuffers();
}

void ModelRenderer::setModelPosition(int x, int y, int z) {
	ModelPosition = glm::vec3(x, y, z);
	modelMatNeedsUpdate = true;
}

void ModelRenderer::remakeIndexBuffer() {
	std::vector<unsigned int> indices;

	Block ** blockArray = parentModel->storage->getBlockArray();

	int modelWidth = parentModel->getWidth();
	int modelHeight = parentModel->getHeight();
	int modelDepth = parentModel->getDepth();

	unsigned int cubeIndexData[] = {
			//Front
			0, 1, 2,
			0, 2, 3,

			//Back
			4, 5, 6,
			4, 6, 7,

			//Left
			8, 9, 10,
			8, 10, 11,

			//Right
			12, 13, 14,
			12, 14, 15,

			//Top
			16, 17, 18,
			16, 18, 19,

			//Bottom
			20, 21, 22,
			20, 22, 23
	};

	for (int x = 0; x < modelWidth; ++x) {
		for (int y = 0; y < modelHeight; ++y) {
			for (int z = 0; z < modelDepth; ++z) {
				int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexXMinusOne = (x - 1) * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexXPlusOne = (x + 1) * modelHeight * modelDepth + y * modelDepth + z;
				int blockIndexYMinusOne = x * modelHeight * modelDepth + (y - 1) * modelDepth + z;
				int blockIndexYPlusOne = x * modelHeight * modelDepth + (y + 1) * modelDepth + z;
				int blockIndexZMinusOne = x * modelHeight * modelDepth + y * modelDepth + z - 1;
				int blockIndexZPlusOne = x * modelHeight * modelDepth + y * modelDepth + z + 1;

				int indexOffset = blockIndex * 24;

				Block * block = blockArray[blockIndex];

				if (block != NULL && block->isDrawn()) {
					if (z != modelDepth - 1) {
						if (blockArray[blockIndexZPlusOne] != NULL && !blockArray[blockIndexZPlusOne]->isDrawn()) { //Front
							for (int i = 0; i < 6; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 0; i < 6; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (z != 0) {
						if (blockArray[blockIndexZMinusOne] != NULL && !blockArray[blockIndexZMinusOne]->isDrawn()) { //Back
							for (int i = 6; i < 12; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 6; i < 12; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (x != 0) {
						if (blockArray[blockIndexXMinusOne] != NULL && !blockArray[blockIndexXMinusOne]->isDrawn()) { //Left
							for (int i = 12; i < 18; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 12; i < 18; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (x != modelWidth - 1) {
						if (blockArray[blockIndexXPlusOne] != NULL && !blockArray[blockIndexXPlusOne]->isDrawn()) { //Right
							for (int i = 18; i < 24; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 18; i < 24; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (y != modelHeight - 1) {
						if (blockArray[blockIndexYPlusOne] != NULL && !blockArray[blockIndexYPlusOne]->isDrawn()) { //Top
							for (int i = 24; i < 30; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 24; i < 30; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}

					if (y != 0) {
						if (blockArray[blockIndexYMinusOne] != NULL && !blockArray[blockIndexYMinusOne]->isDrawn()) { //Bottom
							for (int i = 30; i < 36; ++i) {
								indices.push_back(cubeIndexData[i] + indexOffset);
							}
						}
					} else {
						for (int i = 30; i < 36; ++i) {
							indices.push_back(cubeIndexData[i] + indexOffset);
						}
					}
				}
			}
		}
	}

	numVerticesToDraw = indices.size();

	substituteDataToIndexBuffer(numVerticesToDraw * sizeof(unsigned int), 0, &indices[0]);
}

void ModelRenderer::update(time_t dt) {
	if (parentModel == NULL)
		return;
//	BlockStorage * parentStorage = parentModel->blockStorage;
//	Block ** blockArray = parentStorage->getBlockArray();
//	for (int x = 0; x < Model::Model_SIZE; ++x) {
//		for (int y = 0; y < Model::Model_SIZE; ++y) {
//			for (int z = 0; z < Model::Model_SIZE; ++z) {
//				int blockIndex = x * Model::Model_SIZE * Model::Model_SIZE + y * Model::Model_SIZE + z;
//				if (blockArray[blockIndex]->needsFaceUpdate()) {
//					updateBlockFaces(x, y, z);
//					blockArray[blockIndex]->setNeedsFaceUpdate(false);
//				}
//			}
//		}
//	}

	if (needsIndexBufferRemake) {
		remakeIndexBuffer();
		needsIndexBufferRemake = false;
	}
}

void ModelRenderer::updateBlockFaces(int x, int y, int z) {
	int modelWidth = parentModel->getWidth();
	int modelHeight = parentModel->getHeight();
	int modelDepth = parentModel->getDepth();

	int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
	int blockIndexXMinusOne = (x - 1) * modelHeight * modelDepth + y * modelDepth + z;
	int blockIndexXPlusOne = (x + 1) * modelHeight * modelDepth + y * modelDepth + z;
	int blockIndexYMinusOne = x * modelHeight * modelDepth + (y - 1) * modelDepth + z;
	int blockIndexYPlusOne = x * modelHeight * modelDepth + (y + 1) * modelDepth + z;
	int blockIndexZMinusOne = x * modelHeight * modelDepth + y * modelDepth + z - 1;
	int blockIndexZPlusOne = x * modelHeight * modelDepth + y * modelDepth + z + 1;

	Block ** blockArray = parentModel->storage->getBlockArray();

	unsigned int cubeIndexData[] = {
	//Front
			0, 1, 2,
			0, 2, 3,

			//Back
			4, 5, 6,
			4, 6, 7,

			//Left
			8, 9, 10,
			8, 10, 11,

			//Right
			12, 13, 14,
			12, 14, 15,

			//Top
			16, 17, 18,
			16, 18, 19,

			//Bottom
			20, 21, 22,
			20, 22, 23
	};

	for (int i = 0; i < 36; ++i) {
		cubeIndexData[i] += blockIndex * 24;
	}

	if (z != modelDepth && blockArray[blockIndexZPlusOne]->isDrawn()) {
		for (int i = 0; i < 6; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	if (z != 0 && blockArray[blockIndexZMinusOne]->isDrawn()) {
		for (int i = 6; i < 12; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	if (x != 0 && blockArray[blockIndexXMinusOne]->isDrawn()) {
		for (int i = 12; i < 18; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	if (x != modelWidth - 1 && blockArray[blockIndexXPlusOne]->isDrawn()) {
		for (int i = 18; i < 24; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	if (y != modelHeight - 1 && blockArray[blockIndexYPlusOne]->isDrawn()) {
		for (int i = 24; i < 30; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	if (y != 0 && blockArray[blockIndexYMinusOne]->isDrawn()) {
		for (int i = 30; i < 36; ++i) {
			cubeIndexData[i] = -1;
		}
	}

	substituteDataToIndexBuffer(sizeof(cubeIndexData), blockIndex * 36 * sizeof(unsigned int), cubeIndexData);
}

void ModelRenderer::render(glm::mat4 * viewMatrix) {
	if (modelMatNeedsUpdate) {
		modelMatrix = glm::translate(ModelPosition);
		modelMatNeedsUpdate = false;
	}

	shaderProgram.useProgram();

	shaderProgram.setUniform("modelMatrix", &modelMatrix, 1);
	shaderProgram.setUniform("viewMatrix", viewMatrix, 1);
	shaderProgram.setUniform("projectionMatrix", &projectionMatrix, 1);

	glm::vec3 testColor(1.f, 1.f, 1.f);
	shaderProgram.setUniform("testColor", &testColor, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	int numCubes = parentModel->getWidth() * parentModel->getHeight() * parentModel->getDepth();
	int numVertices = numCubes * 24;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); //Vertices
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 3 * sizeof(float))); //Colors
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) (numVertices * 6 * sizeof(float))); //Normals

	glDrawElements(GL_TRIANGLES, numVerticesToDraw, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glUseProgram(0);
}

void ModelRenderer::updateBlockAtPosition(int x, int y, int z) {
	int modelWidth = parentModel->getWidth();
	int modelHeight = parentModel->getHeight();
	int modelDepth = parentModel->getDepth();
	float cubeSize = parentModel->getScale();
	int blockIndex = x * modelHeight * modelDepth + y * modelDepth + z;
	BlockStorage * blockStorage = parentModel->storage;
	Block * block = blockStorage->getBlockArray()[blockIndex];
	int modelSize = modelWidth * modelHeight * modelDepth;

	int numVerticesPerCube = 24;
	int numVerticesPerModel = numVerticesPerCube * modelSize * 3; //num floats in vertex portion of data
	int numColorsPerModel = numVerticesPerCube * modelSize * 3; //num floats in texture portion of data

	int vertexIndex = blockIndex * numVerticesPerCube * 3;
	int colorIndex = blockIndex * numVerticesPerCube * 3;
	int normalIndex = blockIndex * numVerticesPerCube * 3;

	float cubeVertexData[] = {
			//Front
			0, 0, cubeSize,
			cubeSize, 0, cubeSize,
			cubeSize, cubeSize, cubeSize,
			0, cubeSize, cubeSize,

			//Back
			cubeSize, 0, 0,
			0, 0, 0,
			0, cubeSize, 0,
			cubeSize, cubeSize, 0,

			//Left
			0, 0, 0,
			0, 0, cubeSize,
			0, cubeSize, cubeSize,
			0, cubeSize, 0,

			//Right
			cubeSize, 0, cubeSize,
			cubeSize, 0, 0,
			cubeSize, cubeSize, 0,
			cubeSize, cubeSize, cubeSize,

			//Top
			0, cubeSize, cubeSize,
			cubeSize, cubeSize, cubeSize,
			cubeSize, cubeSize, 0,
			0, cubeSize, 0,

			//Bottom
			0, 0, 0,
			cubeSize, 0, 0,
			cubeSize, 0, cubeSize,
			0, 0, cubeSize
	};

	float cubeColorData[24 * 3];

	float cubeNormalData[] = {
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,

			0, 0, -1,
			0, 0, -1,
			0, 0, -1,
			0, 0, -1,

			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,

			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,

			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,

			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0
	};

	for (int i = 0; i < 24; ++i) {
		cubeVertexData[(i * 3)] += x;
		cubeVertexData[(i * 3) + 1] += y;
		cubeVertexData[(i * 3) + 2] += z;

		cubeColorData[(i * 3)] = block->getColor().r;
		cubeColorData[(i * 3) + 1] = block->getColor().g;
		cubeColorData[(i * 3) + 2] = block->getColor().b;
	}

	substituteDataToVertexBuffer(sizeof(cubeVertexData), vertexIndex * sizeof(float), cubeVertexData);
	substituteDataToVertexBuffer(sizeof(cubeColorData), (numVerticesPerModel + colorIndex) * sizeof(float), (float *)cubeColorData);
	substituteDataToVertexBuffer(sizeof(cubeNormalData), (numVerticesPerModel + numColorsPerModel + normalIndex) * sizeof(float), cubeNormalData);
	markDirty();
}

void ModelRenderer::markDirty() {
	needsIndexBufferRemake = true;
}
