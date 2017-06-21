//
// Created by marc on 21/06/17.
//

#include "vulkan_system/validation_layers.h"

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
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		if (!layerFound)
			return false;
	}
	return true;
}

std::vector<const char*> ValidationLayers::getRequiredExtensions()
{
	std::vector<const char*> result;
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (unsigned int i = 0; i < glfwExtensionCount; i++)
	    result.push_back(glfwExtensions[i]);
	if (ENABLE_VALIDATION_LAYERS)
	    result.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	return result;
}
