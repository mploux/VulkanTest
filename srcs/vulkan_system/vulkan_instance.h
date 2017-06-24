//
// Created by marc on 21/06/17.
//

#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "validation_layers.h"
#include "utils.h"

class VulkanInstance
{
private:
	VkInstance					m_instance;
	VkDebugReportCallbackEXT	m_callback;
	ValidationLayers			m_layers;

	void init();
	void initDebugCallbacks();

public:
	VulkanInstance(ValidationLayers layers);
	~VulkanInstance();

	inline VkInstance getInstance() { return (m_instance); }
	inline ValidationLayers getValidationLayers() { return (m_layers); }
};
