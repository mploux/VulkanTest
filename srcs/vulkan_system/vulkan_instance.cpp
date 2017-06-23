//
// Created by marc on 21/06/17.
//

#include "vulkan_instance.h"

VulkanInstance::VulkanInstance(ValidationLayers layers):
		m_layers{layers}
{
	VkApplicationInfo		appInfo;
	VkInstanceCreateInfo	instanceInfo;
	unsigned int			glfwExtensionCount = 0;
	const char				**glfwExtensions;

	if (ENABLE_VALIDATION_LAYERS && !m_layers.checkValidationLayerSupport())
		throw std::runtime_error("validation layers requested, but not available!");

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Yeay title";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Whops no engine for the moment";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pApplicationInfo = &appInfo;
	instanceInfo.enabledExtensionCount = glfwExtensionCount;
	instanceInfo.ppEnabledExtensionNames = glfwExtensions;
	instanceInfo.flags = 0;

	if (ENABLE_VALIDATION_LAYERS)
	{
		std::vector<const char *> extensions = m_layers.getRequiredExtensions();
		for (int i = 0; i < extensions.size(); i++)
			std::cerr << extensions[i] << std::endl;
		instanceInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		instanceInfo.ppEnabledExtensionNames = extensions.data();
	}
	else
		instanceInfo.enabledLayerCount = 0;
	if (vkCreateInstance(&instanceInfo, nullptr, &m_instance) != VK_SUCCESS)
		throw std::runtime_error("failed to create vulkan instance !");
}

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(m_instance, NULL);
}
