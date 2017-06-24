//
// Created by marc on 21/06/17.
//

#pragma once

#include <cstdint>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "vulkan_instance.h"

class							VulkanInstance;

typedef struct					_VulkanQueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
}								VulkanQueueFamilyIndices;

typedef struct					_SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR 		capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> 	presentModes;
}								SwapChainSupportDetails;

void 							printVulkanExtensions();
VkResult 						CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
void 							DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
std::vector<const char*> 		getRequiredExtensions();
VulkanQueueFamilyIndices 		findQueueFamilies(VulkanInstance *instance, VkPhysicalDevice device);
bool							isValideDevice(VulkanInstance *instance, VkPhysicalDevice device);
bool							checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char *> deviceExtensions);
bool							checkValidationLayerSupport(std::vector<const char *> layer);

SwapChainSupportDetails			querySwapChainSupport(VulkanInstance *instance, VkPhysicalDevice device);
VkSurfaceFormatKHR				chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR				chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
VkExtent2D						chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

const char*						getVulkanResult(VkResult code);

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
{
	std::cerr << "Vulkan validation layer: " << msg << std::endl;
	return VK_FALSE;
}
