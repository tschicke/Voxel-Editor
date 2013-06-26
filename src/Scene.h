/*
 * Scene.h
 *
 *  Created on: Jan 30, 2013
 *      Author: Tyler
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <GL/glew.h>
#include <SFML/Window/Event.hpp>

#include "Common.h"

class Scene {//: public Drawable{
public:
	Scene();
	virtual ~Scene();

	virtual void handleInput() = 0;
	virtual void update(time_t dt) = 0;
	virtual void draw() = 0;
private:
};

#endif /* SCENE_H_ */
