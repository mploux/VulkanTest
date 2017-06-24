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

#include "vulkan_instance.h"

class VulkanInstance;

typedef struct	_VulkanQueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
}				VulkanQueueFamilyIndices;

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugReportFlagsEXT flags,
	VkDebugReportObjectTypeEXT objType,
	uint64_t obj, size_t location, int32_t code,
	const char* layerPrefix, const char* msg, void* userData)
{
	std::cerr << "Vulkan validation layer: " << msg << std::endl;
	return VK_FALSE;
}

void printVulkanExtensions();

VkResult CreateDebugReportCallbackEXT(
	VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback);

void DestroyDebugReportCallbackEXT(
	VkInstance instance,
	VkDebugReportCallbackEXT callback,
	const VkAllocationCallbacks* pAllocator);

std::vector<const char*> getRequiredExtensions();
VulkanQueueFamilyIndices findQueueFamilies(VulkanInstance *instance, VkPhysicalDevice device);
bool isValideDevice(VulkanInstance *instance, VkPhysicalDevice device);

bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char *> deviceExtensions);

bool checkValidationLayerSupport(std::vector<const char *> layer);

static const char* getVulkanResult(VkResult code)
{
	switch (code)
	{
		case VK_SUCCESS:
			return "Vulkan : Command successfully completed";
			break;
		case VK_NOT_READY:
			return "Vulkan : A fence or query has not yet completed";
			break;
		case VK_TIMEOUT:
			return "Vulkan : A wait operation has not completed in the "
				   "specified time";
			break;
		case VK_EVENT_SET:
			return "Vulkan : An event is signaled";
			break;
		case VK_EVENT_RESET:
			return "Vulkan : An event is unsignaled";
			break;
		case VK_INCOMPLETE:
			return "Vulkan : A return array was too small for the result";
			break;

		case VK_ERROR_OUT_OF_HOST_MEMORY:
			return "Vulan : A host memory allocation has failed";
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			return "Vulkan : A device memory allocation has failed";
			break;
		case VK_ERROR_INITIALIZATION_FAILED:
			return "Vulkan : Initialization of an object could not be "
				   "completed";
			break;
		case VK_ERROR_DEVICE_LOST:
			return "Vulkan : The logical or physical device has been lost";
			break;
		case VK_ERROR_MEMORY_MAP_FAILED:
			return "Vulkan : Mapping of a memory object has failed";
			break;
		case VK_ERROR_LAYER_NOT_PRESENT:
			return "Vulkan: A requested layer is not present or could not "
				   "be loaded";
			break;
		case VK_ERROR_EXTENSION_NOT_PRESENT:
			return "Vulkan : A requested extension is not supported";
			break;
		case VK_ERROR_FEATURE_NOT_PRESENT:
			return "Vulkan : A requested feature is not supported";
			break;
		case VK_ERROR_INCOMPATIBLE_DRIVER:
			return "Vulkan : The requested version of Vulkan is not "
				   "supported by the driver or is otherwise incompatible";
			break;
		case VK_ERROR_TOO_MANY_OBJECTS:
			return "Vulkan : Too many objects of the type have already "
				   "been created";
			break;
		case VK_ERROR_FORMAT_NOT_SUPPORTED:
			return "Vulkan : A requested format is not supported on this "
				   "device";
			break;
		case VK_ERROR_FRAGMENTED_POOL:
			return "Vulkan : A requested pool allocation has failed due to "
				   "fragmentation of the pool’s memory";
			break;

		/* Extra */
		case VK_ERROR_VALIDATION_FAILED_EXT:
			return "Vulkan : VK_ERROR_VALIDATION_FAILED_EXT";
			break;

		case VK_RESULT_RANGE_SIZE:
			return "Vulkan : VK_RESULT_RANGE_SIZE";
			break;

		case VK_SUBOPTIMAL_KHR:
			return "Vulkan : VK_SUBOPTIMAL_KHR";
			break;

		case VK_RESULT_MAX_ENUM:
			return "Vulkan : VK_RESULT_MAX_ENUM";
			break;

		/* KHR */
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			return "Vulkan : VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
			break;
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			return "Vulkan : VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
			break;
		case VK_ERROR_SURFACE_LOST_KHR:
			return "Vulkan : VK_ERROR_SURFACE_LOST_KHR";
			break;
		case VK_ERROR_OUT_OF_DATE_KHR:
			return "Vulkan : VK_ERROR_OUT_OF_DATE_KHR";
			break;

		/* Nvidia */
		case VK_ERROR_INVALID_SHADER_NV:
			return "Vulkan : VK_ERROR_INVALID_SHADER_NV";
			break;
	}
	return "Vulkan : Unknow error";
}
