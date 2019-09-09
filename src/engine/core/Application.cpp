#include "Includes.h"

#include "Application.h"

Application *Application::instance = nullptr;

Application::Application() {
	instance = this;

	appWindow = std::unique_ptr<Window>(Window::Create());
	appWindow->setEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

}

Application::~Application() {
	for (auto &layer : layerStack) {
		layer.reset();
	}

	Renderer::destroyRenderer();
	ImportManager::destroyManager();
	appWindow.reset();
}

void Application::Run() {
	while (running) {

		for (auto &layer : layerStack) {
			layer->onUpdate();
		}

		appWindow->onUpdate();
	}
}

void Application::OnEvent(Event &e) {
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));

	for (auto it = layerStack.end(); it != layerStack.end();) {
		(*--it)->onEvent(e);
		if (e.handled) {
			break;
		}
	}
}

void Application::pushLayer(std::unique_ptr<Layer> layer) {
	layerStack.pushLayer(std::move(layer));
}

void Application::pushOverlay(std::unique_ptr<Layer> overlay) {
	layerStack.pushOverlay(std::move(overlay));
}

bool Application::onWindowClose(WindowCloseEvent &e) {
	running = false;
	return true;
}