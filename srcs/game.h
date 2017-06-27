//
// Created by marc on 21/06/17.
//

#pragma once

#include "vulkan_system/vulkan_instance.h"

class Game
{
private:
	VulkanInstance	*m_vulkan;
	GLFWwindow		*m_window;

public:
	Game(GLFWwindow *window, int width, int height);
	~Game();

	void update();
	void render(int width, int height);
};
