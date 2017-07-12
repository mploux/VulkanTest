//
// Created by marc on 21/06/17.
//

#pragma once

#include "cutils.h"
#include <cstdint>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <fstream>
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
VkExtent2D						chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t width, uint32_t height);

uint32_t						findMemoryType(VkPhysicalDevice m_physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
void 							copyBuffer(VulkanInstance *instance, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

const char*						getVulkanResult(VkResult code);

VkShaderModule					createShaderModule(VulkanInstance *instance, const std::vector<char>& code);

VkFormat						findSupportedFormat(VulkanInstance *instance, const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
VkFormat						findDepthFormat(VulkanInstance *instance);

bool							hasStencilComponent(VkFormat format);

std::vector<char>				readFile(const std::string &filename);

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	switch (flags)
	{
		case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
			std::cerr << T_RED << "VK INFO(" << code << "): " << T_YEL << msg << T_NRM << std::endl;
			break;
		case VK_DEBUG_REPORT_WARNING_BIT_EXT:
			std::cerr << T_RED << "VK WARNING(" << code << "): " << T_YEL << msg << T_NRM << std::endl;
			break;
		case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT :
			std::cerr << T_RED << "VK PERF WARNING(" << code << "): " << T_YEL << msg << T_NRM << std::endl;
			break;
		case VK_DEBUG_REPORT_ERROR_BIT_EXT :
			std::cerr << T_RED << "VK ERROR(" << code << "): " << T_YEL << msg << T_NRM << std::endl;
			break;
		case VK_DEBUG_REPORT_DEBUG_BIT_EXT :
			std::cerr << T_RED << "VK DEBUG(" << code << "): " << T_YEL << msg << T_NRM << std::endl;
			break;
	}
	return VK_FALSE;
}
