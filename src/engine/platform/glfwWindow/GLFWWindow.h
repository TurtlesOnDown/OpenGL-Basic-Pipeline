#pragma once

#include "../../core/Window.h"

class GLFWWindowClass : public Window {
public:
	GLFWWindowClass(const WindowConfigs &c);

	virtual ~GLFWWindowClass() override;

	virtual void onUpdate() override;

	virtual unsigned int getWidth() const override { return data.width; };
	virtual unsigned int getHeight() const override { return data.height; };

	virtual void setEventCallback(const EventCallbackFunc &callback) override { data.EventCallback = callback; }

	virtual void *getPlatformWindow() const override { return window; };
private:
	GLFWwindow *window;

	struct GLFWWindowData {
		std::string name;
		unsigned int width;
		unsigned int height;

		EventCallbackFunc EventCallback;
	};

	GLFWWindowData data;

private:
	virtual void Init(const WindowConfigs &c);
	virtual void Destroy();
};
