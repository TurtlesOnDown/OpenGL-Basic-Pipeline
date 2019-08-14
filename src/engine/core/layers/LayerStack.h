#pragma once

#include "Layer.h"


class LayerStack {
public:
	LayerStack();
	~LayerStack();

	void pushLayer(std::unique_ptr<Layer> layer);
	void pushOverlay(std::unique_ptr<Layer> overlay);
	void popLayer(std::unique_ptr<Layer> layer);
	void popOverlay(std::unique_ptr<Layer> overlay);

	std::vector<std::unique_ptr<Layer>>::iterator begin() { return layers.begin(); }
	std::vector<std::unique_ptr<Layer>>::iterator end() { return layers.end(); }

private:
	std::vector<std::unique_ptr<Layer>> layers;
	unsigned int layerInsertIndex;
};