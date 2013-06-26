/*
 * Editor.h
 *
 *  Created on: Jun 23, 2013
 *      Author: Tyler
 */

#ifndef EDITOR_H_
#define EDITOR_H_

#include "CubeModel.h"

class Editor {
public:
	Editor();
	virtual ~Editor();

private:
	int modelWidth, modelHeight, modelDepth;//Width = x, Height = y, Depth = z

	CubeModel model;
};

#endif /* EDITOR_H_ */
