#pragma once

#include "Event.h"

class KeyEvent : public Event {
public:
	inline int getKeyCode() const { return keyCode; }

	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_KEYBOARD | EVENT_CATEGORY::EV_INPUT; }
protected:
	KeyEvent(int code) : keyCode(code) {

	}

	int keyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
	KeyPressedEvent(int code, int repeatCount) : KeyEvent(code), repeats(repeatCount) {}

	inline int getRepeatCount() const { return repeats; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "KEY_PRESSED::" << keyCode << "::REPEATS::" << repeats;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::KEY_PRESSED; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "KEY_PRESSED"; }

private:
	int repeats;
};

class KeyReleasedEvent : public KeyEvent {
public:
	KeyReleasedEvent(int code) : KeyEvent(code) {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "KEY_RELEASED::" << keyCode;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::KEY_RELEASED; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "KEY_RELEASED"; }

};

class KeyTypedEvent : public KeyEvent {
public:
	KeyTypedEvent(int code) : KeyEvent(code) {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "KEY_TYPED::" << keyCode;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::KEY_TYPED; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "KEY_TYPED"; }

};