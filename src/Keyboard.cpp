/*
 * Keyboard.cpp
 *
 *  Created on: Mar 14, 2013
 *      Author: Tyler
 */

#include "Keyboard.h"

#include <iostream>

namespace ts {

bool Keyboard::keys[];
Keyboard::KeyEventType Keyboard::keyEvents[];

Keyboard::Keyboard() {

}

Keyboard::~Keyboard() {
}

void Keyboard::init(){
	for (int i = 0; i < keyCount; i++){
		keys[i] = false;
		keyEvents[i] = defaultEventType;
	}
}

void Keyboard::clearEvents(){
	for (int i = 0; i < keyCount; i++){
		keyEvents[i] = defaultEventType;
	}
}

void Keyboard::setKey(int key, bool value){
	keys[key] = value;
}

bool Keyboard::isKeyPressed(Key key){
	return keys[key];
}

void Keyboard::setKeyEvent(int key, KeyEventType type){
	keyEvents[key] = type;
}

Keyboard::KeyEventType Keyboard::checkKeyEvent(Key key){
	return keyEvents[key];
}

} /* namespace ts */
