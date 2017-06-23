//
// Created by marc on 21/06/17.
//

#include "game.h"

Game::Game()
{
	ValidationLayers vulkan_layers = ValidationLayers();
	vulkan_layers.addLayer("VK_LAYER_LUNARG_standard_validation");

	m_vulkan = new VulkanInstance(vulkan_layers);
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
