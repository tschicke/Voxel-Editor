/*
 * Slider.cpp
 *
 *  Created on: Jun 25, 2013
 *      Author: Tyler
 */

#include "Slider.h"

#include <gl/glew.h>

Slider::Slider() {
	init(0, 0, 200, 200);
}

Slider::Slider(int width, int height) {
	init(0, 0, width, height);
}

Slider::Slider(int x, int y, int width, int height) {
	init(x, y, width, height);
}

void Slider::init(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	sliderX = width / 2;
}

Slider::~Slider() {
}

bool Slider::isInBounds(int checkX, int checkY) {
	return (checkX >= x && checkX <= x + width && checkY >= y && checkY <= y + height);
}

float Slider::getValue() {
	return (float) sliderX / (float) width;
}

void Slider::setSliderX(int x) {
	sliderX = x;
}

int Slider::getX() {
	return x;
}

int Slider::getY() {
	return y;
}

void Slider::draw(){
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(x, y + (height / 2));//Main line
	glVertex2f(x + width, y + (height / 2));

	glVertex2f(x, y);
	glVertex2f(x, y + height);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x + sliderX, y);
	glVertex2f(x + sliderX, y + height);

	glEnd();
}
