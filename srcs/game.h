//
// Created by marc on 21/06/17.
//

#pragma once

#include "vulkan_system/vulkan_instance.h"
#include "vulkan_system/validation_layers.h"

class Game
{
private:
	VulkanInstance *m_vulkan;

public:
	Game();
	~Game();

	void update();
	void render();
};
