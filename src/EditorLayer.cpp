/*
 * EditorLayer.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "EditorLayer.h"
#include "Keyboard.h"

#include <fstream>
#include <iostream>

EditorLayer::EditorLayer() {
	createNewModel();
	selector = ColorSelector(20, 20, 300, 100);
}

EditorLayer::~EditorLayer() {
	delete model;
}

void EditorLayer::update(time_t dt) {
	selector.update(dt);
	model->setColor(selector.getColor());
	model->update(dt);
}

void EditorLayer::handleInput() {
	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::Space) == ts::Keyboard::keyPressed) {
		SelectedBlock block = model->getSelectedBlock();
		model->setColor(block.block->getColor());
		selector.setColor(block.block->getColor());
	}
	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::L) == ts::Keyboard::keyPressed) {
		loadModel();
	}
	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::S) == ts::Keyboard::keyPressed) {
		saveModel();
	}
	if (ts::Keyboard::checkKeyEvent(ts::Keyboard::N) == ts::Keyboard::keyPressed) {
		createNewModel();
	}
	selector.input();
}

void EditorLayer::draw() {
	model->draw();
	selector.draw();
}

void EditorLayer::loadModel() {
	char fileName[30];
	std::cout << "Enter File Name\n";
	std::cin >> fileName;
	std::ifstream file;
	file.open(fileName, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Couldn't open file: " << fileName << '\n';
		return;
	}

	char header[14];
	file.read(header, 14);
	if (header[0] != 'c' || header[1] != 'm') {
		std::cout << "wrong file format\n";
		return;
	}

	int width = *(int *) &header[2];
	int height = *(int *) &header[6];
	int depth = *(int *) &header[10];

	delete model;
	model = new CubeModel(width, height, depth);
	model->load(fileName);
}

void EditorLayer::saveModel() {
	char fileName[30];
	std::cout << "Enter File Name\n";
	std::cin >> fileName;
	std::ofstream file;
	file.open(fileName, std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Couldn't open file: " << fileName << '\n';
		return;
	}

	model->save(fileName);
}

void EditorLayer::createNewModel() {
	unsigned int width, height, depth;

	std::cout << "Enter width\n";
	std::cin >> width;
	std::cout << "Enter height\n";
	std::cin >> height;
	std::cout << "Enter depth\n";
	std::cin >> depth;

	model = new CubeModel(width, height, depth); //Why does this need to be a pointer?
}
