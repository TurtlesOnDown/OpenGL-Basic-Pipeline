#pragma once

#include "Includes.h"

#include <GLFW/glfw3.h>
#include "events/Event.h"

struct WindowConfigs {
	std::string name = "Default Name";
	unsigned int width = 1280;
	unsigned int height = 720;

	WindowConfigs(const std::string &n = "Default Name",
		unsigned int w = 1280, 
		unsigned int h = 720): name(n), width(w), height(h){

	}
};

class Window {
public:
	using EventCallbackFunc = std::function<void(Event &)>;

	virtual ~Window() = default;

	virtual void onUpdate() = 0;

	virtual unsigned int getWidth() const = 0;
	virtual unsigned int getHeight() const = 0;

	virtual void setEventCallback(const EventCallbackFunc &callback) = 0; // TODO: Make event system

	virtual void *getPlatformWindow() const = 0;

	static Window *Create(const WindowConfigs &configs = WindowConfigs());
};