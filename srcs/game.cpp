//
// Created by marc on 21/06/17.
//

#include "game.h"

Game::Game(GLFWwindow *window)
{
	std::vector<const char *> vulkanValidationLayers = {};
	vulkanValidationLayers.push_back("VK_LAYER_LUNARG_standard_validation");

	std::vector<const char *> vulkanDeviceExtensions = {};
	vulkanDeviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	m_vulkan = new VulkanInstance(vulkanValidationLayers, vulkanDeviceExtensions);
	m_vulkan->initDebugCallbacks();
	m_vulkan->initWindowSurface(window);
	m_vulkan->initPhysicalDevices();
	m_vulkan->createLogicalDevices(1.0);
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
