#include "utils.h"

void printVulkanExtensions()
{
	uint32_t extensionCount = 0;

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	std::cout << "Available vulkan extensions:" << std::endl;
	for (const auto& extension : extensions)
		std::cout << "\t" << extension.extensionName << std::endl;
}

VkResult CreateDebugReportCallbackEXT(
	VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugReportCallbackEXT(
	VkInstance instance,
	VkDebugReportCallbackEXT callback,
	const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

std::vector<const char*> getRequiredExtensions()
{
	std::vector<const char*>	result;
	unsigned int				glfwExtensionCount = 0;
	const char					**glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	for (unsigned int i = 0; i < glfwExtensionCount; i++)
	{
		result.push_back(glfwExtensions[i]);
	}
	if (ENABLE_VALIDATION_LAYERS)
		result.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	return result;
}

VulkanQueueFamilyIndices findQueueFamilies(VulkanInstance *instance, VkPhysicalDevice device)
{
	VulkanQueueFamilyIndices indices;

	uint32_t count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(count);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queueFamilies.data());

	for (int i = 0; i < queueFamilies.size(); i++)
	{
		VkQueueFamilyProperties queueFamily = queueFamilies[i];
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, instance->getSurface(), &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport)
			indices.presentFamily = i;

		if (indices.isComplete())
			break;
	}

	return indices;
}

SwapChainSupportDetails querySwapChainSupport(VulkanInstance *instance, VkPhysicalDevice device)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, instance->getSurface(), &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, instance->getSurface(), &formatCount, nullptr);
	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, instance->getSurface(), &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, instance->getSurface(), &presentModeCount, nullptr);
	if (presentModeCount != 0)
	{
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, instance->getSurface(), &presentModeCount, details.presentModes.data());
	}
	return details;
}

bool isValideDevice(VulkanInstance *instance, VkPhysicalDevice device)
{
	VulkanQueueFamilyIndices indices = findQueueFamilies(instance, device);
	bool extensionsSupported = checkDeviceExtensionSupport(device, instance->getDeviceExtensions());
	bool swapChainAdequate = false;

	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(instance, device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	for (const auto& availableFormat : availableFormats)
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			return availableFormat;
	return availableFormats[0];
}

/*
	VK_PRESENT_MODE_IMMEDIATE_KHR: Images submitted by your application are
			transferred to the screen right away, which may result in tearing.
	VK_PRESENT_MODE_FIFO_KHR: The swap chain is a queue where the display
			takes an image from the front of the queue on a vertical blank
			and the program inserts rendered images at the back of the queue.
			If the queue is full then the program has to wait. This is most
			similar to vertical sync as found in modern games.
	VK_PRESENT_MODE_FIFO_RELAXED_KHR: This mode only differs from the previous
			one if the application is late and the queue was empty at the last
			vertical blank. Instead of waiting for the next vertical blank,
			the image is transferred right away when it finally arrives.
			This may result in visible tearing.
	VK_PRESENT_MODE_MAILBOX_KHR: This is another variation of the second mode.
			Instead of blocking the application when the queue is full, the
			images that are already queued are simply replaced with the newer
			ones. This mode can be used to implement triple buffering, which
			allows you to avoid tearing with significantly less latency issues
			than standard vertical sync that uses double buffering.
*/
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return availablePresentMode;
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			bestMode = availablePresentMode;
	}
	return bestMode;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		return capabilities.currentExtent;

	VkExtent2D actualExtent = {1280, 720}; //TODO: handle proper resolution
	actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
	actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
	return actualExtent;
}

bool checkDeviceExtensionSupport(VkPhysicalDevice device, std::vector<const char *> deviceExtensions)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

bool checkValidationLayerSupport(std::vector<const char *> layers)
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : layers)
	{
		bool layerFound = false;
		for (const auto& layerProperties : availableLayers)
		{
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

VkShaderModule createShaderModule(VulkanInstance *instance, const std::vector<char>& code)
{
	VkShaderModule shaderModule;

	VkShaderModuleCreateInfo shaderInfo = {};
	shaderInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderInfo.codeSize = code.size();
	shaderInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(instance->getDevice(), &shaderInfo, nullptr, &shaderModule) != VK_SUCCESS)
	    throw std::runtime_error("Vulkan failed to create shader module!");
	return (shaderModule);
}

std::vector<char> readFile(const std::string &filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
		throw std::runtime_error("failed to open file!");

	size_t fileSize = (size_t) file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	return buffer;
}

const char*				getVulkanResult(VkResult code)
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
