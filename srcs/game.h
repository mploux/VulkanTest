//
// Created by marc on 21/06/17.
//

#pragma once

#include "vulkan_system/vulkan_instance.h"

class Game
{
private:
	VulkanInstance	*m_vulkan;

public:
	Game(GLFWwindow *window);
	~Game();

	void update();
	void render();
};
