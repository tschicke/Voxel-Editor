/*
 * ColorSelector.h
 *
 *  Created on: Jun 25, 2013
 *      Author: Tyler
 */

#ifndef COLORSELECTOR_H_
#define COLORSELECTOR_H_

#include "Slider.h"

#include <glm/glm.hpp>
#include "Common.h"

class ColorSelector {
public:
	ColorSelector();
	ColorSelector(int width, int height);
	ColorSelector(int x, int y, int width, int height);
	virtual ~ColorSelector();

	void init(int x, int y, int width, int height);

	glm::vec3 getColor();

	void update(time_t dt);
	void input();
	void draw();

private:
	glm::vec3 color;

	int x, y, width, height;

	Slider redSlider, greenSlider, blueSlider;
};

#endif /* COLORSELECTOR_H_ */
