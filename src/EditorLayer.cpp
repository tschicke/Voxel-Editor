/*
 * EditorLayer.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "EditorLayer.h"
#include "Keyboard.h"

#include <iostream>

EditorLayer::EditorLayer() {
	unsigned int width, height, depth;

	std::cout << "Enter width\n";
	std::cin >> width;
	std::cout << "Enter height\n";
	std::cin >> height;
	std::cout << "Enter depth\n";
	std::cin >> depth;

	model = new CubeModel(width, height, depth); //Why does this need to be a pointer?
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
	if(ts::Keyboard::checkKeyEvent(ts::Keyboard::Space) == ts::Keyboard::keyPressed){
		SelectedBlock block = model->getSelectedBlock();
		model->setColor(block.block->getColor());
		selector.setColor(block.block->getColor());
	}
	selector.input();
}

void EditorLayer::draw() {
	model->draw();
	selector.draw();
}
