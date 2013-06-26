/*
 * ColorSelector.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: Tyler
 */

#include "ColorSelector.h"

#include "Mouse.h"

#include <gl/glew.h>

#include <iostream>

ColorSelector::ColorSelector() {
	init(0, 0, 200, 200);
}

ColorSelector::ColorSelector(int width, int height) {
	init(0, 0, width, height);
}

ColorSelector::ColorSelector(int x, int y, int width, int height) {
	init(x, y, width, height);
}

void ColorSelector::init(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	color = glm::vec3(1, 1, 1);

	int sliderOffsetX = 5;
	int sliderOffsetY = 5;

	int sliderSpacingY = (height - (sliderOffsetY * 2)) / 3;

	int sliderWidth = width - (2 * sliderOffsetX);
	int sliderHeight = (height - (2 * sliderOffsetY)) / 3;

	redSlider = Slider(x + sliderOffsetX, y + sliderOffsetY + sliderHeight + sliderHeight + sliderSpacingY + sliderSpacingY, sliderWidth, sliderHeight);
	greenSlider = Slider(x + sliderOffsetX, y + sliderOffsetY + sliderHeight + sliderSpacingY, sliderWidth, sliderHeight);
	blueSlider = Slider(x + sliderOffsetX, y + sliderOffsetY, sliderWidth, sliderHeight);
}

ColorSelector::~ColorSelector() {
}

glm::vec3 ColorSelector::getColor() {
	return color;
}

void ColorSelector::update(time_t dt) {
	color.r = redSlider.getValue();
	color.g = greenSlider.getValue();
	color.b = blueSlider.getValue();
}

void ColorSelector::input() {
	if (ts::Mouse::isButtonPressed(ts::Mouse::Button0)) {
		glm::vec2 mousePos = ts::Mouse::getPosition();
		mousePos.y = 600 - mousePos.y;
		if(redSlider.isInBounds(mousePos.x, mousePos.y)){
			redSlider.setSliderX(mousePos.x - redSlider.getX());
		} else if(greenSlider.isInBounds(mousePos.x, mousePos.y)){
			greenSlider.setSliderX(mousePos.x - greenSlider.getX());
		} else if(blueSlider.isInBounds(mousePos.x, mousePos.y)){
			blueSlider.setSliderX(mousePos.x - blueSlider.getX());
		}
	}
}

void ColorSelector::draw() {
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);

	glLineWidth(2.f);

	redSlider.draw();
	greenSlider.draw();
	blueSlider.draw();


	glBegin(GL_TRIANGLES);
	glColor3f(color.r, color.g, color.b);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glVertex2f(20, 20);
	glVertex2f(0, 0);
	glVertex2f(20, 20);
	glVertex2f(0, 20);
	glEnd();

	glEnable(GL_DEPTH_TEST);
}
