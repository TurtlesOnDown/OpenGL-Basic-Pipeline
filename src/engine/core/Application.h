#pragma once

#include "Window.h"
#include "events/Event.h"
#include "../import manager/ImportManager.h"
#include "../graphics/renderer/Renderer.h"
#include "layers/LayerStack.h"

class Application {
public:
	Application();

	virtual ~Application() = default;

	void Run();

	void OnEvent(Event &e); // TODO: Event system

	void pushLayer(std::unique_ptr<Layer> layer);
	void pushOverlay(std::unique_ptr<Layer> overlay);

	inline Window &GetWindow() { return *appWindow; };

	inline static Application &Get() { return *instance; };
private:
	LayerStack layerStack;
	std::unique_ptr<Window> appWindow;

	bool running = true;
private:
	static Application *instance;
};

Application *CreateApplication(); // To be define by client