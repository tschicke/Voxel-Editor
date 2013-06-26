/*
 * Mouse.cpp
 *
 *  Created on: Mar 16, 2013
 *      Author: Tyler
 */

#include <iostream>

#include "Mouse.h"

namespace ts {

bool Mouse::buttons[];
Mouse::MouseButtonEventType Mouse::buttonEvents[];

glm::vec2 Mouse::position;
bool Mouse::locked;
int Mouse::lastDX, Mouse::lastDY;

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

void Mouse::init() {
	locked = false;
	lastDX = 0;
	lastDY = 0;

	for (int i = 0; i < buttonCount; i++) {
		buttons[i] = false;
		buttonEvents[i] = defaultEventType;
	}
}

void Mouse::setPosition(int x, int y) {
	position = glm::vec2(x, y);
}

glm::vec2 Mouse::getPosition() {
	return position;
}

void Mouse::movePosition(int dx, int dy) {
	position += glm::vec2(dx, dy);
}

void Mouse::setLastMove(int dx, int dy) {
	lastDX = dx;
	lastDY = dy;
}

glm::vec2 Mouse::getLastMove() {
	return glm::vec2(lastDX, lastDY);
}

void Mouse::setLocked(bool isLocked) {
	locked = isLocked;
}

bool Mouse::isLocked() {
	return locked;
}

void Mouse::clearEvents() {
	for (int i = 0; i < buttonCount; ++i) {
		buttonEvents[i] = defaultEventType;
	}
}

void Mouse::setButton(int button, bool value) {
	buttons[button] = value;
}

bool Mouse::isButtonPressed(Button button) {
	return buttons[button];
}

void Mouse::setMouseButtonEvent(int button, MouseButtonEventType type) {
	buttonEvents[button] = type;
}

Mouse::MouseButtonEventType Mouse::checkMouseButtonEvent(Button button) {
	return buttonEvents[button];
}
} /* namespace ts */
