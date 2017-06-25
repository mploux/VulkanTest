//
// Created by marc on 21/06/17.
//

#include "game.h"

Game::Game(GLFWwindow *window)
{
	std::vector<const char *> vulkanDeviceExtensions = {};
	vulkanDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	m_vulkan = new VulkanInstance(vulkanDeviceExtensions);
	m_vulkan->initDebugCallbacks();
	m_vulkan->initWindowSurface(window);
	m_vulkan->initPhysicalDevices();
	m_vulkan->createLogicalDevices(1.0);
	m_vulkan->createSwapChain();
	m_vulkan->createRenderPass();
	m_vulkan->createImageViews();
	m_vulkan->createFramebuffers();
	m_vulkan->createCommandPool();
	m_vulkan->createCommandBuffers();
	m_vulkan->createSemaphores();
}

Game::~Game()
{
	delete m_vulkan;
}

void Game::update()
{

}

void Game::render()
{

}
