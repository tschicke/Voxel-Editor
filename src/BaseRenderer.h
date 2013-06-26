/*
 * ChunkRenderer.h
 *
 *  Created on: May 18, 2013
 *      Author: Tyler
 */

#ifndef BASERENDERER_H_
#define BASERENDERER_H_

#include "Common.h"

#include "Shader.h"
#include <glm/glm.hpp>

class Player;//Should be include?

class BaseRenderer {
public:
	BaseRenderer();
	virtual ~BaseRenderer();

	void initBuffersWithSize(int vertexBufferSize, int indexBufferSize);
	void deleteBuffers();

	void substituteDataToVertexBuffer(int size, int offset, float * data);
	void substituteDataToVertexBuffer(int size, int offset, int * data);

	void substituteDataToIndexBuffer(int size, int offset, unsigned int * data);

	void bindVertexBuffer(); //should be bindArrayBuffer?
	void bindIndexBuffer(); //should be bindIndexArrayBuffer?

	void unbindVertexBuffer(); //should be bindArrayBuffer?
	void unbindIndexBuffer(); //should be bindIndexArrayBuffer?

	void translateModelMatrix(float x, float y, float z);

	void render(Player * player);

	static void setProjectionMatrix();
	static glm::mat4 * getProjectionMatrix();

protected:
	uint vertexBufferID, indexBufferID;
	bool vertBuffLoaded, indexBuffLoaded;

	ShaderProgram shaderProgram;

	glm::mat4 modelMatrix;

	static glm::mat4 projectionMatrix;

	static float fov;
};

#endif /* BASERENDERER_H_ */
