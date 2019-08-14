#pragma once

#include "Event.h"

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(float x, float y) : mouseX(x), mouseY(y) {}

	inline int getX() const { return mouseX; }
	inline int getY() const { return mouseY; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "MOUSE_MOVE::X::" << mouseX << "::Y::" << mouseY;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::MOUSE_MOVE; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "MOUSE_MOVE"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_MOUSE | EVENT_CATEGORY::EV_INPUT; }

private:
	float mouseX;
	float mouseY;
};

class MouseScrollEvent : public Event {
public:
	MouseScrollEvent(float x, float y) : offsetX(x), offsetY(y) {}

	inline int getX() const { return offsetX; }
	inline int getY() const { return offsetY; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "MOUSE_SCROLL::XOffset::" << offsetX << "::XOffset::" << offsetY;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::MOUSE_SCROLL; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "MOUSE_SCROLL"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_MOUSE | EVENT_CATEGORY::EV_INPUT; }

private:
	float offsetX;
	float offsetY;
};

class MouseButtonEvent : public Event {
public:
	inline int getMouseButton() const { return button; }

	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_MOUSE_BUTTON | EVENT_CATEGORY::EV_INPUT; }

protected:
	MouseButtonEvent(int b):button(b) {}

	int button;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
	MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "MOUSE_PRESS::" << button;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::MOUSE_PRESS; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "MOUSE_PRESS"; }

};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
	MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "MOUSE_RELEASE::" << button;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::MOUSE_RELEASE; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "MOUSE_RELEASE"; }

};