//
// Created by marc on 21/06/17.
//

#include "game.h"

bool resizing = false;

static void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (width == 0 || height == 0)
		return;
	// VulkanInstance* vulkan = reinterpret_cast<VulkanInstance*>(glfwGetWindowUserPointer(window));
	// vulkan->recreateSwapChain((uint32_t)width, (uint32_t)height);
	resizing = true;
}

Game::Game(GLFWwindow *window, int width, int height):
	m_window {window}
{
	std::vector<const char *> validationLayers = {};
	validationLayers.push_back("VK_LAYER_LUNARG_standard_validation");

	std::vector<const char *> vulkanDeviceExtensions = {};
	vulkanDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	m_vulkan = new VulkanInstance(validationLayers, vulkanDeviceExtensions);
	m_vulkan->initDebugCallbacks();
	m_vulkan->initWindowSurface(window);
	m_vulkan->initPhysicalDevices();
	m_vulkan->createLogicalDevices(1.0);
	m_vulkan->createSwapChain((uint32_t)width, (uint32_t)height);
	m_vulkan->createRenderPass();
	m_vulkan->createGraphicsPipeline();
	m_vulkan->createImageViews();
	m_vulkan->createFramebuffers();
	m_vulkan->createCommandPool();
	m_vulkan->createCommandBuffers();
	m_vulkan->createSemaphores();

	glfwSetWindowUserPointer(window, m_vulkan);
	glfwSetWindowSizeCallback(window, &onWindowResized);
}

Game::~Game()
{
	delete m_vulkan;
}

void Game::update()
{
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	if (resizing)
		m_vulkan->recreateSwapChain((uint32_t)width, (uint32_t)height);
	resizing = false;
}

void Game::render(int width, int height)
{
	m_vulkan->drawFrame((uint32_t)width, (uint32_t)height);
	//vkDeviceWaitIdle(m_vulkan->getDevice());
}
