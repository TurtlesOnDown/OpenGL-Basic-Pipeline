#include <Includes.h>

#include "Layer.h"

Layer::Layer(const std::string &name):layerName(name) {

}

/*Layer::Layer(const Layer &other) {
	layerName = other.layerName;
}

Layer &Layer::operator=(const Layer &other) {
	layerName = other.layerName;
	return *this;
}

Layer::Layer(Layer &&other) {
	layerName = other.layerName;
}

Layer &Layer::operator=(Layer &&other) {
	layerName = other.layerName;
	return *this;
}*/