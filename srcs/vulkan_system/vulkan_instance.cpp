//
// Created by marc on 21/06/17.
//

#include "vulkan_instance.h"

VulkanInstance::VulkanInstance(std::vector<const char *> layers, std::vector<const char *> extension):
		m_validationLayers {layers},
		m_deviceExtensions {extension},
		m_physicalDevice {VK_NULL_HANDLE}
{
	if (ENABLE_VALIDATION_LAYERS && !checkValidationLayerSupport(m_validationLayers))
		throw std::runtime_error("Vulkan validation layers requested, but not available !");

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Yeay title";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Whops no engine for the moment";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo instanceInfo;
	std::vector<const char *> extensions = getRequiredExtensions();
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	instanceInfo.ppEnabledExtensionNames = extensions.data();

	if (ENABLE_VALIDATION_LAYERS)
	{
		std::cout << "Number of layers:    " << static_cast<uint32_t>(m_validationLayers.size()) << std::endl;
		std::cout << "Layer name:    " << m_validationLayers[0] << std::endl;

		instanceInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
		instanceInfo.ppEnabledLayerNames = m_validationLayers.data();
	}
	else
		instanceInfo.enabledLayerCount = 0;

	VkResult res = vkCreateInstance(&instanceInfo, nullptr, &m_instance);
	if (res != VK_SUCCESS)
	{
		std::cerr << "ERROR: " << getVulkanResult(res) << std::endl;
		throw std::runtime_error("Failed to create vulkan instance !");
	}
}

void VulkanInstance::initDebugCallbacks()
{
	if (!ENABLE_VALIDATION_LAYERS)
		return;

	VkDebugReportCallbackCreateInfoEXT debugInfo;
	debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	debugInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	debugInfo.pfnCallback = debugCallback;
	if (CreateDebugReportCallbackEXT(m_instance, &debugInfo, nullptr, &m_callback) != VK_SUCCESS)
		throw std::runtime_error("Vulkan failed to set up debug callback!");
}

void VulkanInstance::initWindowSurface(GLFWwindow *window)
{
	if (glfwCreateWindowSurface(m_instance, window, nullptr, &m_surface) != VK_SUCCESS)
		throw std::runtime_error("Vulkan failed to create window surface!");
}

void VulkanInstance::initPhysicalDevices()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		throw std::runtime_error("Vulkan failed to find GPUs with Vulkan support!");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (isValideDevice(this, device))
		{
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE)
		throw std::runtime_error("Vulkan failed to find a valide GPU!");
}

void VulkanInstance::createLogicalDevices(float priority)
{
	VulkanQueueFamilyIndices indices = findQueueFamilies(this, m_physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueInfos;
	std::set<int> uniqueQueueFamilies = {
		indices.graphicsFamily,
		indices.presentFamily
	};

	float queuePriority = 1.0f;
	for (int queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueInfo = {};
		queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueInfo.queueFamilyIndex = queueFamily;
		queueInfo.queueCount = 1;
		queueInfo.pQueuePriorities = &queuePriority;
		queueInfos.push_back(queueInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo deviceInfo = {};
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueInfos.size());
	deviceInfo.pQueueCreateInfos = queueInfos.data();
	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pEnabledFeatures = &deviceFeatures;
	deviceInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtensions.size());
	deviceInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

	if (ENABLE_VALIDATION_LAYERS)
	{
		deviceInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
		deviceInfo.ppEnabledLayerNames = m_validationLayers.data();
	} else
		deviceInfo.enabledLayerCount = 0;

	if (vkCreateDevice(m_physicalDevice, &deviceInfo, nullptr, &m_device) != VK_SUCCESS)
		throw std::runtime_error("Vulkan failed to create logical device!");

	vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, indices.presentFamily, 0, &m_presentQueue);
}

void VulkanInstance::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = querySwapChainSupport(this, m_physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		imageCount = swapChainSupport.capabilities.maxImageCount;

	VkSwapchainCreateInfoKHR swapChainInfo = {};
	swapChainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapChainInfo.surface = m_surface;
	swapChainInfo.minImageCount = imageCount;
	swapChainInfo.imageFormat = surfaceFormat.format;
	swapChainInfo.imageColorSpace = surfaceFormat.colorSpace;
	swapChainInfo.imageExtent = extent;
	swapChainInfo.imageArrayLayers = 1;
	swapChainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	VulkanQueueFamilyIndices indices = findQueueFamilies(this, m_physicalDevice);
	uint32_t queueFamilyIndices[] = {(uint32_t) indices.graphicsFamily, (uint32_t) indices.presentFamily};

	if (indices.graphicsFamily != indices.presentFamily)
	{
		swapChainInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapChainInfo.queueFamilyIndexCount = 2;
		swapChainInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		swapChainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapChainInfo.queueFamilyIndexCount = 0;
		swapChainInfo.pQueueFamilyIndices = nullptr;
	}

	swapChainInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	swapChainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapChainInfo.presentMode = presentMode;
	swapChainInfo.clipped = VK_TRUE;
	swapChainInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_device, &swapChainInfo, nullptr, &m_swapChain) != VK_SUCCESS)
		throw std::runtime_error("Vulkan failed to create swap chain!");

	vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
	m_swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

	m_swapChainImageFormat = surfaceFormat.format;
	m_swapChainExtent = extent;
}

void VulkanInstance::createImageViews()
{
	m_swapChainImageViews.resize(m_swapChainImages.size());
	for (size_t i = 0; i < m_swapChainImages.size(); i++)
	{
		VkImageViewCreateInfo imageInfo = {};
		imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		imageInfo.image = m_swapChainImages[i];
		imageInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		imageInfo.format = m_swapChainImageFormat;
		imageInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		imageInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageInfo.subresourceRange.baseMipLevel = 0;
		imageInfo.subresourceRange.levelCount = 1;
		imageInfo.subresourceRange.baseArrayLayer = 0;
		imageInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_device, &imageInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
    		throw std::runtime_error("failed to create image views!");
	}
}

VulkanInstance::~VulkanInstance()
{
	for (size_t i = 0; i < m_swapChainImageViews.size(); i++)
		vkDestroyImageView(m_device, m_swapChainImageViews[i], nullptr);
	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
	vkDestroyDevice(m_device, nullptr);
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);
	DestroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
	//vkDestroyInstance(m_instance, nullptr); // This thing SEGVs. I'm not sure why, I'l found out later.
}
