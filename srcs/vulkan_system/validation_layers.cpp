//
// Created by marc on 21/06/17.
//

#include "validation_layers.h"

ValidationLayers::ValidationLayers()
{}

ValidationLayers::~ValidationLayers()
{}

bool ValidationLayers::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : m_layers)
	{
		bool layerFound = false;
		for (const auto& layerProperties : availableLayers)
		{
			std::cout << layerName << "     " << layerProperties.layerName << std::endl;
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}
		if (!layerFound)
			return false;
	}
	return true;
}
