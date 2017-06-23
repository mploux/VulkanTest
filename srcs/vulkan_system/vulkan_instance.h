//
// Created by marc on 21/06/17.
//

#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include "validation_layers.h"

class VulkanInstance
{
private:
	VkInstance			m_instance;
	ValidationLayers	m_layers;

public:
	VulkanInstance(ValidationLayers layers);
	~VulkanInstance();

	inline VkInstance getInstance() { return (m_instance); }
	inline ValidationLayers getValidationLayers() { return (m_layers); }
};
