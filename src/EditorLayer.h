/*
 * EditorLayer.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#ifndef EDITORLAYER_H_
#define EDITORLAYER_H_

#include "Layer.h"

#include "CubeModel.h"
#include "ColorSelector.h"

class EditorLayer: public Layer {
public:
	EditorLayer();
	virtual ~EditorLayer();

	void update(time_t dt);
	void handleInput();
	void draw();

private:
	CubeModel * model;
	ColorSelector selector;

	void loadModel();
	void saveModel();

	void createNewModel();
};

#endif /* EDITORLAYER_H_ */
