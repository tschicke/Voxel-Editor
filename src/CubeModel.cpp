/*
 * CubeModel.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "CubeModel.h"

#include "Keyboard.h"
#include "Mouse.h"

#include "BaseRenderer.h"

#include <glm/gtx/transform.hpp>

#include <fstream>

#include <iostream>

#include <cmath>

CubeModel::CubeModel() {
	width = height = depth = 0;
	scale = 1;
	selectedBlock.x = selectedBlock.y = selectedBlock.z = 0;
	yaw = 0;
	pitch = 0;
	viewMatrixNeedsUpdate = false;
	zoom = 1;

	storage = NULL;
}

CubeModel::CubeModel(int w, int h, int d) {
	width = w;
	height = h;
	depth = d;
	scale = 1;
	yaw = 0;
	pitch = 0;
	viewMatrixNeedsUpdate = true;

	int maxHeightDepth = (height > depth ? height : depth);
	int maxWidthHeightDepth = (width > maxHeightDepth ? width : maxHeightDepth);
	zoom = maxWidthHeightDepth;

	selectedBlock.x = selectedBlock.y = selectedBlock.z = 0;

	storage = new BlockStorage(this);
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			for (int z = 0; z < d; ++z) {
				int blockIndex = x * h * d + y * d + z;
				Block * block = new Block(1, 0, 0, true);
				storage->getBlockArray()[blockIndex] = block;
			}
		}
	}

	renderer = ModelRenderer(0, 0, 0, this);
}

CubeModel::~CubeModel() {
	storage->freeArray();
}

int CubeModel::getWidth() {
	return width;
}

int CubeModel::getHeight() {
	return height;
}

int CubeModel::getDepth() {
	return depth;
}

float CubeModel::getScale() {
	return scale;
}

void CubeModel::update(time_t dt) {
	handleInput();

	if (viewMatrixNeedsUpdate) {
		glm::vec3 center(width / 2.f, height / 2.f, depth / 2.f);
		glm::vec3 position;

		float yawR = yaw * 3.14159265f / 180;
		float pitchR = pitch * 3.14159265 / 180;

		position.x = sinf(yawR) * cosf(pitchR);
		position.y = sinf(pitchR);
		position.z = cosf(yawR) * cosf(pitchR);

		position *= zoom;

		position += center;

		viewMatrix = glm::lookAt(position, center, glm::vec3(0, 1, 0));
		viewMatrixNeedsUpdate = false;
	}

	raytraceBlocks();

	renderer.update(dt);
}

void CubeModel::handleInput() {
	if (ts::Mouse::isButtonPressed(ts::Mouse::Button2)) {
		int mouseDX = ts::Mouse::getLastMove().x, mouseDY = ts::Mouse::getLastMove().y;
		pitch -= mouseDY;
		yaw -= mouseDX;

		yaw %= 360;

		if (pitch < -89) {
			pitch = -89;
		}

		if (pitch > 89) {
			pitch = 89;
		}

		viewMatrixNeedsUpdate = true;
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::S) == ts::Keyboard::keyPressed) {
		save();
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::L) == ts::Keyboard::keyPressed) {
		load();
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Up) == ts::Keyboard::keyPressed) {
		zoom -= 1;
		int maxHeightDepth = (height > depth ? height : depth);
		int maxWidthHeightDepth = (width > maxHeightDepth ? width : maxHeightDepth);
		if (zoom < maxWidthHeightDepth / 2) {
			zoom = maxWidthHeightDepth / 2;
		}
		viewMatrixNeedsUpdate = true;
	}

	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Down) == ts::Keyboard::keyPressed) {
		zoom += 1;
		int maxHeightDepth = (height > depth ? height : depth);
		int maxWidthHeightDepth = (width > maxHeightDepth ? width : maxHeightDepth);
		if (zoom > maxWidthHeightDepth * 2) {
			zoom = maxWidthHeightDepth * 2;
		}
		viewMatrixNeedsUpdate = true;
	}

	if (ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button0) == ts::Mouse::buttonPressed) {
		if (selectedBlock.block != NULL) {
			Block * block = storage->getBlockArray()[selectedBlock.x * height * depth + selectedBlock.y * depth + selectedBlock.z];

			block->setDrawn(false);
			renderer.markDirty();
		}
	}
	if (ts::Mouse::checkMouseButtonEvent(ts::Mouse::Button1) == ts::Mouse::buttonPressed) {
		if (selectedBlock.block != NULL) {
			glm::vec3 placeBlockPos = selectedBlock.getAddBlockPosition();
			if (placeBlockPos.x >= 0 && placeBlockPos.x <= width - 1 && placeBlockPos.y >= 0 && placeBlockPos.y <= height - 1 && placeBlockPos.z >= 0 && placeBlockPos.z <= depth - 1) {
				Block * block = storage->getBlockArray()[(int) placeBlockPos.x * height * depth + (int) placeBlockPos.y * depth + (int) placeBlockPos.z];
				if (!block->isDrawn()) {

					block->setColor(currentColor);
					block->setDrawn(true);
					renderer.updateBlockAtPosition(placeBlockPos.x, placeBlockPos.y, placeBlockPos.z);
				}
			}
		}
	}
}

void CubeModel::draw() {
	renderer.render(&viewMatrix);
}

void CubeModel::setColor(glm::vec3 color) {
	currentColor = color;
}

void CubeModel::save() {
	char fileName[30];
	std::cout << "enter save file name\n";
	std::cin >> fileName;
	std::ofstream file(fileName, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "file couldn't be opened\n";
		return;
	}

	const char * identifier = "cm";
	file.write(identifier, 2);
	file.write((char *) &width, 4);
	file.write((char *) &height, 4);
	file.write((char *) &depth, 4);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int z = 0; z < depth; ++z) {
				int blockIndex = x * height * depth + y * depth + z;
				Block * block = storage->getBlockArray()[blockIndex];

				bool isDrawn = block->isDrawn();
				glm::vec3 blockColor = block->getColor();
				file.write((char *) &isDrawn, 1);
				file.write((char *) &(blockColor.x), 4);
				file.write((char *) &(blockColor.y), 4);
				file.write((char *) &(blockColor.z), 4);
			}
		}
	}

	file.close();
}

void CubeModel::load() {
	char fileName[30];
	std::cout << "enter file name to load from\n";
	std::cin >> fileName;
	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "file could not be opened\n";
		return;
	}

	char identifier[2];
	file.read(&identifier[0], 1);
	file.read(&identifier[1], 1);
	if (!(identifier[0] == 'c' && identifier[1] == 'm')) {
		std::cout << "wrong file format\n";
		return;
	}

	char header[12];

	file.read(header, 12);

	width = *(int *) &header[0];
	height = *(int *) &header[4];
	depth = *(int *) &header[8];

	int numCubes = width * height * depth;
	int bytesPerCube = 13;
	int bufferSize = numCubes * bytesPerCube;
	char * buffer = new char[bufferSize];

	file.read(buffer, bufferSize);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int z = 0; z < depth; ++z) {
				int blockIndex = x * height * depth + y * depth + z;
				Block * block = storage->getBlockArray()[blockIndex];

				bool drawn = *(bool *) &buffer[blockIndex * bytesPerCube];
				glm::vec3 blockColor;

				blockColor.x = *(float *) &buffer[blockIndex * bytesPerCube + 1];
				blockColor.y = *(float *) &buffer[blockIndex * bytesPerCube + 5];
				blockColor.z = *(float *) &buffer[blockIndex * bytesPerCube + 9];

				block->setDrawn(drawn);
				block->setColor(blockColor);

				renderer.updateBlockAtPosition(x, y, z);
			}
		}
	}

	renderer.markDirty();

	file.close();
}

void CubeModel::raytraceBlocks() {
	glm::vec2 mousePos = ts::Mouse::getPosition();
	glm::vec3 startPos = glm::unProject(glm::vec3(mousePos.x, 600 - mousePos.y, 0.f), viewMatrix, *(BaseRenderer::getProjectionMatrix()), glm::vec4(0, 0, 800, 600));
	glm::vec3 endPos = glm::unProject(glm::vec3(mousePos.x, 600 - mousePos.y, 1.f), viewMatrix, *(BaseRenderer::getProjectionMatrix()), glm::vec4(0, 0, 800, 600));

	bool posXChange = endPos.x > startPos.x;
	bool posYChange = endPos.y > startPos.y;
	bool posZChange = endPos.z > startPos.z;

	int startX = (posXChange ? floorf(startPos.x) : ceilf(startPos.x));
	int endX = (posXChange ? ceilf(endPos.x) : floorf(endPos.x));
	int startY = (posYChange ? floorf(startPos.y) : ceilf(startPos.y));
	int endY = (posYChange ? ceilf(endPos.y) : floorf(endPos.y));
	int startZ = (posZChange ? floorf(startPos.z) : ceilf(startPos.z));
	int endZ = (posZChange ? ceilf(endPos.z) : floorf(endPos.z));

	int xChange = (posXChange ? 1 : -1);
	int yChange = (posYChange ? 1 : -1);
	int zChange = (posZChange ? 1 : -1);

	for (int x = startX; x != endX + xChange; x += xChange) {
		for (int y = startY; y != endY + yChange; y += yChange) {
			for (int z = startZ; z != endZ + zChange; z += zChange) {
				if (x >= 0 && x < width && y >= 0 && y < height && z >= 0 && z < depth) {
					int blockIndex = x * height * depth + y * depth + z;
					Block * currentBlock = storage->getBlockArray()[blockIndex];
					if (currentBlock->isDrawn()) {
						Face face = currentBlock->raytrace(x, y, z, startPos, endPos);
						if (face != face_nocollision) {
							selectedBlock = SelectedBlock(x, y, z, currentBlock, face);
							return;
						}
					}
				}
			}
		}
	}

	selectedBlock = SelectedBlock(0, 0, 0, NULL, face_nocollision);
}
