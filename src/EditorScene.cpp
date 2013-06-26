/*
 * EditorScene.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "EditorScene.h"

#include <gl/glew.h>

EditorScene::EditorScene() {

}

EditorScene::~EditorScene() {
}

void EditorScene::handleInput() {
	editorLayer.handleInput();
}

void EditorScene::update(time_t dt) {
	editorLayer.update(dt);
}

void EditorScene::draw() {
	editorLayer.draw();
}
