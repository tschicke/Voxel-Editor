/*
 * EditorScene.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#ifndef EDITORSCENE_H_
#define EDITORSCENE_H_

#include "Scene.h"
#include "EditorLayer.h"

class EditorScene : public Scene{
public:
	EditorScene();
	virtual ~EditorScene();

	void handleInput();
	void update(time_t dt);
	void draw();
private:
	EditorLayer editorLayer;
};

#endif /* EDITORSCENE_H_ */
