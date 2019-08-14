#pragma once

#include "Event.h"

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(unsigned int w, unsigned int h): width(w), height(h) {}

	inline unsigned int getWidth() const { return width; }
	inline unsigned int getHeight() const { return height; }

	std::string toString() const override {
		std::stringstream ss;
		ss << "WINDOW_RESIZE::WIDTH::" << width << "::HEIGHT::" << height;
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::WINDOW_RESIZE; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "WINDOW_RESIZE"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_APPLICATION; }

private:
	unsigned int width, height;
};

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent() {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "WINDOW_CLOSE";
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::WINDOW_CLOSE; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "WINDOW_CLOSE"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_APPLICATION; }

};

class AppTickEvent : public Event {
	AppTickEvent() {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "APP_TICK";
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::APP_TICK; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "APP_TICK"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_APPLICATION; }
};

class AppUpdateEvent : public Event {
	AppUpdateEvent() {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "APP_UPDATE";
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::APP_UPDATE; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "APP_UPDATE"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_APPLICATION; }
};

class AppRenderEvent : public Event {
	AppRenderEvent() {}

	std::string toString() const override {
		std::stringstream ss;
		ss << "APP_RENDER";
		return ss.str();
	}

	static EVENT_TYPE getStaticType() { return EVENT_TYPE::APP_RENDER; }
	virtual EVENT_TYPE getEventType() const override { return getStaticType(); }
	virtual const char *getName() const override { return "APP_RENDER"; }
	virtual int getCategoryFlags() const override { return EVENT_CATEGORY::EV_APPLICATION; }
};