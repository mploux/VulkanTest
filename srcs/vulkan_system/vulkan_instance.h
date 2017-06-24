//
// Created by marc on 21/06/17.
//

#pragma once

#ifdef DEBUG
# define ENABLE_VALIDATION_LAYERS 1
#else
# define ENABLE_VALIDATION_LAYERS 0
#endif

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <set>

#include "utils.h"

class VulkanInstance
{
private:
	VkInstance						m_instance;
	VkDebugReportCallbackEXT		m_callback;
	VkSurfaceKHR					m_surface;

	VkPhysicalDevice				m_physicalDevice;
	VkDevice						m_device;

	VkQueue							m_graphicsQueue;
	VkQueue							m_presentQueue;

	VkSwapchainKHR					m_swapChain;
	std::vector<VkImage>			m_swapChainImages;
	VkFormat						m_swapChainImageFormat;
	VkExtent2D						m_swapChainExtent;
	std::vector<VkImageView> 		m_swapChainImageViews;

	std::vector<const char *>		m_validationLayers;
	std::vector<const char *> 		m_deviceExtensions;

public:
	VulkanInstance(std::vector<const char *> layers, std::vector<const char *> extensions);
	~VulkanInstance();

	void initDebugCallbacks();
	void initWindowSurface(GLFWwindow *window);
	void initPhysicalDevices();
	void createLogicalDevices(float priority);
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();

	inline VkInstance getInstance() { return (m_instance); }
	inline VkSurfaceKHR getSurface() { return (m_surface); }
	inline VkPhysicalDevice getPhysicalDevice() { return (m_physicalDevice); }
	inline VkDevice getDevice() { return (m_device); }

	inline std::vector<const char *> getValidationLayers() { return (m_validationLayers); }
	inline std::vector<const char *> getDeviceExtensions() { return (m_deviceExtensions); }
};
