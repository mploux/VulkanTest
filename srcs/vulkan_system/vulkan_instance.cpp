//
// Created by marc on 21/06/17.
//

#include "vulkan_instance.h"

VulkanInstance::VulkanInstance(ValidationLayers layers):
		m_layers{layers}
{
	init();
	initDebugCallbacks();
}

void VulkanInstance::init()
{

	if (ENABLE_VALIDATION_LAYERS && !m_layers.checkValidationLayerSupport())
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
		std::cout << "YOLO    " << static_cast<uint32_t>(m_layers.getLayers().size()) << std::endl;
		std::cout << "YOLO    " << m_layers.getLayers()[0] << std::endl;

		instanceInfo.enabledLayerCount = static_cast<uint32_t>(m_layers.getLayers().size());
		instanceInfo.ppEnabledLayerNames = m_layers.getLayers().data();
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

VulkanInstance::~VulkanInstance()
{
	DestroyDebugReportCallbackEXT(m_instance, m_callback, nullptr);
	vkDestroyInstance(m_instance, nullptr);
}
