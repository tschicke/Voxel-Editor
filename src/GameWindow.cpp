/*
 * GameWindow.cpp
 *
 *  Created on: Jan 27, 2013
 *      Author: Tyler
 */

#include <iostream>

#include <gl/glew.h>

#include "GameWindow.h"

#include "Keyboard.h"
#include "Mouse.h"

using namespace sf;

GameWindow::GameWindow() {
	currentScene = NULL;
	title = NULL;
	width = 0;
	height = 0;
	fpsCounter = 0;
	running = false;
}

GameWindow::GameWindow(int w, int h, const char * title) {
	create(w, h, title);
}

GameWindow::~GameWindow() {
}

void GameWindow::create(int w, int h, const char * title) {
	width = w;
	height = h;
	this->title = title;
	running = false;
	create(VideoMode(w, h, 32), title);
//	setVerticalSyncEnabled(true);
	setFramerateLimit(30);
	init();
	initGL();
}

void GameWindow::init() {
	ts::Keyboard::init();
	ts::Mouse::init();
//	setMouseCursorVisible(false);
}

void GameWindow::initGL() {
	glViewport(0, 0, width, height);
	glClearColor(0, 100.f / 255, 200.f / 255, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW did not initialize properly\n";
	}
}

void GameWindow::setScene(Scene * scene) {
	currentScene = scene;
}

Scene * GameWindow::getCurrentScene() {
	return currentScene;
}

void GameWindow::run() {
	running = true;

	long dt;

	Clock clock;
	while (running) {
		dt = clock.restart().asMilliseconds();
		handleInput();
		update(dt);
		render();
		ts::Keyboard::clearEvents();
		ts::Mouse::clearEvents();
		fpsCounter += dt;
		if (fpsCounter >= 1000) {
			std::cout << 1000.f / dt << std::endl;
			fpsCounter = 0;
		}
	}
	cleanUp();
}

void GameWindow::handleInput() {
	Event event;
	ts::Mouse::setLastMove(0, 0); //Temp fix
	while (pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			ts::Keyboard::setKey(event.key.code, true);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyPressed);
		} else if (event.type == sf::Event::KeyReleased) {
			ts::Keyboard::setKey(event.key.code, false);
			ts::Keyboard::setKeyEvent(event.key.code, ts::Keyboard::keyReleased);
		} else if (event.type == sf::Event::MouseMoved) {
			int dx = 0, dy = 0;
			dx = (event.mouseMove.x - ts::Mouse::getPosition().x);
			dy = -(event.mouseMove.y - ts::Mouse::getPosition().y);
			ts::Mouse::setLastMove(dx, dy);
			if (ts::Mouse::isLocked()) {
				lockMouse(event.mouseMove.x, event.mouseMove.y);
			} else {
				ts::Mouse::setPosition(event.mouseMove.x, event.mouseMove.y);
			}
		} else if(event.type == sf::Event::MouseButtonPressed){
			ts::Mouse::setButton(event.mouseButton.button, true);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonPressed);
		} else if(event.type == sf::Event::MouseButtonReleased){
			ts::Mouse::setButton(event.mouseButton.button, false);
			ts::Mouse::setMouseButtonEvent(event.mouseButton.button, ts::Mouse::buttonReleased);
		} else if(event.type == sf::Event::MouseWheelMoved){
		}

		if (event.type == Event::Closed) {
			running = false;
		} else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			running = false;
		}
	}

	currentScene->handleInput();
}

void GameWindow::update(time_t dt) {
	currentScene->update(dt);
}

void GameWindow::render() { //Watch for too high framerate
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currentScene->draw();

	display();
}

void GameWindow::lockMouse(int mouseX, int mouseY) {
	int xDist = mouseX - (width / 2), yDist = mouseY - (height / 2);
	int distSqr = (xDist * xDist) + (yDist * yDist);
	if (distSqr >= 90000) {//Temp
		sf::Mouse::setPosition(sf::Vector2i(width / 2, height / 2), *this);
		ts::Mouse::setPosition(width / 2, height / 2);
	} else {
		ts::Mouse::setPosition(mouseX, mouseY);
	}
}

void GameWindow::cleanUp() {
}

