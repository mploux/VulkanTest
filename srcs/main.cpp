//
// Created by marc on 21/06/17.
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>
#include "game.h"

#include "vulkan_system/utils.h"

using namespace std;

GLFWwindow *createWindow(string title, int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	return (glfwCreateWindow(width, height, title.c_str(), NULL, NULL));
}

int main()
{
	GLFWwindow	*window = createWindow("Vulkan test", 1280, 720);
	Game *game = new Game(window);

	double lastTime = glfwGetTime();
	while(!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastTime > 1000.0 / 60.0)
		{
		}
		game->update();
		game->render();
		glfwPollEvents();
	}
	delete game;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
