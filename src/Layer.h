/*
 * Layer.h
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#ifndef LAYER_H_
#define LAYER_H_

#include <vector>

#include "Common.h"

class Layer{
public:
	Layer();
	virtual ~Layer();

	virtual void update(time_t dt) = 0;
	virtual void draw() = 0;
	virtual void handleInput() = 0;

private:
//	std::vector<Drawable *> children;
};

#endif /* LAYER_H_ */
