#pragma once

#include "../events/Event.h"

class Layer {
public:
	Layer(const std::string &name = "DefaultLayerName");
	virtual ~Layer() = default;
	/*Layer(const Layer &other);
	Layer &operator=(const Layer &other);
	Layer(Layer &&other);
	Layer &operator=(Layer &&other);*/

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate() {}
	virtual void onEvent(Event &event) {}

	inline const std::string &getName() const { return layerName; }
private:
	std::string layerName;
};