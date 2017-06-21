//
// Created by marc on 21/06/17.
//

#pragma once

#ifdef NDEBUG
# define ENABLE_VALIDATION_LAYERS false
#else
# define ENABLE_VALIDATION_LAYERS true
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>

class ValidationLayers
{
private:
	std::vector<const char*> m_layers;

public:
	ValidationLayers();
	~ValidationLayers();

	bool						checkValidationLayerSupport();
	std::vector<const char*>	getRequiredExtensions();

	inline void addLayer(const char* layer) { m_layers.push_back(layer); }
	inline std::vector<const char*> getLayers() { return (m_layers); }
};
