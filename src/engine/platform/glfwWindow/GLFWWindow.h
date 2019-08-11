#pragma once

#include "../../core/Window.h"

class GLFWWindowClass : public Window {
public:
	GLFWWindowClass(const WindowConfigs &c);

	virtual ~GLFWWindowClass() override;

	virtual void onUpdate() override {}; // TODO: Make event system

	virtual unsigned int getWidth() const override { return config.width; };
	virtual unsigned int getHeight() const override { return config.height; };

	virtual void setEventCallback() override {}; // TODO: Make event system

	virtual void *getPlatformWindow() const override { return window; };
private:
	GLFWwindow *window;

	struct GLFWWindowConfig {
		std::string name;
		unsigned int width;
		unsigned int height;
	};

	GLFWWindowConfig config;

private:
	virtual void Init(const WindowConfigs &c);
	virtual void Destroy();
};
