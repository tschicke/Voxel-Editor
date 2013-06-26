/*
 * EditorLayer.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "EditorLayer.h"

#include <iostream>

EditorLayer::EditorLayer() {
	model = new CubeModel(32, 64, 32);//Why does this need to be a pointer?
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
	selector.input();
}

void EditorLayer::draw() {
	model->draw();
	selector.draw();
}
