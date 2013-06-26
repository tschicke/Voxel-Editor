/*
 * Mouse.h
 *
 *  Created on: Mar 16, 2013
 *      Author: Tyler
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <glm/glm.hpp>

namespace ts {

class Mouse { //TODO add buttons to mouse class
public:
	enum Button {
		Button0,
		Button1,
		Button2,

		buttonCount
	};

	enum MouseButtonEventType {
		defaultEventType,
		buttonPressed,
		buttonReleased
	};

	static void init();

	static void setPosition(int x, int y);
	static glm::vec2 getPosition();
	static void movePosition(int dx, int dy);

	static void setLastMove(int dx, int dy);
	static glm::vec2 getLastMove();

	static void setLocked(bool isLocked);
	static bool isLocked();

	static void clearEvents();

	static void setButton(int button, bool value);
	static bool isButtonPressed(Button button);

	static void setMouseButtonEvent(int button, MouseButtonEventType type);
	static MouseButtonEventType checkMouseButtonEvent(Button button);
private:
	Mouse();
	Mouse(const Mouse& mouse);
	Mouse& operator=(Mouse const& mouse);
	virtual ~Mouse();

	static bool locked;
	static glm::vec2 position;
	static int lastDX, lastDY;

	static bool buttons[buttonCount];
	static MouseButtonEventType buttonEvents[buttonCount];
};

} /* namespace ts */
#endif /* MOUSE_H_ */
