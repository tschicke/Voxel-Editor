/*
 * main.cpp
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#include "src/GameWindow.h"
#include "src/EditorScene.h"

int main(){
	GameWindow window;
	window.create(800, 600, "Voxel Editor");
	window.setScene(new EditorScene);
	window.run();
}

