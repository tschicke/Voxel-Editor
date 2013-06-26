/*
 * Slider.h
 *
 *  Created on: Jun 25, 2013
 *      Author: Tyler
 */

#ifndef SLIDER_H_
#define SLIDER_H_

class Slider {
public:
	Slider();
	Slider(int width, int height);
	Slider(int x, int y, int width, int height);
	virtual ~Slider();

	void init(int x, int y, int width, int height);

	bool isInBounds(int x, int y);

	void setSliderX(int x);

	float getValue();

	int getX();
	int getY();

	void draw();
private:
	int x, y, width, height;

	int sliderX;
};

#endif /* SLIDER_H_ */
