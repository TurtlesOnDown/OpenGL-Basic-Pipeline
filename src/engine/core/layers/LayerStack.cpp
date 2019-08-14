#include <Includes.h>

#include "LayerStack.h"

LayerStack::LayerStack() {

}

LayerStack::~LayerStack() {

}

void LayerStack::pushLayer(std::unique_ptr<Layer> layer) {
	auto it = layers.emplace(layers.begin() + layerInsertIndex, std::move(layer));
	layerInsertIndex++;
	(*it)->onAttach();
}

void LayerStack::pushOverlay(std::unique_ptr<Layer> overlay) {
	layers.emplace_back(std::move(overlay));
	(*layers.end())->onAttach();
}

void LayerStack::popLayer(std::unique_ptr<Layer> layer) {
	auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
	if (it != layers.end()) {
		layer->onDetach();
		layers.erase(it);
		layerInsertIndex--;
	}
}

void LayerStack::popOverlay(std::unique_ptr<Layer> overlay) {
	auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
	if (it != layers.end()) {
		overlay->onDetach();
		layers.erase(it);
	}
}