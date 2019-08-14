#pragma once

#include <Includes.h>

enum class EVENT_TYPE {
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOSE_FOCUS, WINDOW_MOVED,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
	MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOVE, MOUSE_SCROLL
};

enum EVENT_CATEGORY {
	NONE = 0,
	EV_APPLICATION = (1 << 0),
	EV_INPUT = (1 << 1),
	EV_KEYBOARD = (1 << 2),
	EV_MOUSE = (1 << 3),
	EV_MOUSE_BUTTON = (1 << 4),
};

class Event {
public:
	bool handled = false;

	virtual EVENT_TYPE getEventType() const = 0;
	virtual const char *getName() const = 0;
	virtual int getCategoryFlags() const = 0;
	virtual std::string toString() const { return getName(); }

	inline bool isInCategory(EVENT_CATEGORY cat) {
		return getCategoryFlags() &cat;
	}
};

class EventDispatcher {
public:

	EventDispatcher(Event &e):event(e) {

	}

	template<typename T>
	bool dispatch(std::function<bool(T &)> func) {
		if (event.getEventType() == T::GetStaticType()) {
			event.handled = func(*(T*)&event);
			return true;
		}
		return false;
	}

private:
	Event &event;
};