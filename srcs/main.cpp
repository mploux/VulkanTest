//
// Created by marc on 21/06/17.
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>
#include "game.h"

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
	Game *game = new Game(window, 1280, 720);

	double lastTime = 0;
	int frames = 0;
	int ticks = 0;
	while(!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastTime > 1.0 / 60.0)
		{
			game->update();
			ticks++;
			if (ticks % 60 == 0)
			{
				std::cout << "FPS: " << frames << std::endl;
				frames = 0;
			}
			lastTime += 1.0 / 60.0;
		}
		else
		{
			game->render();
			frames++;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;
		glfwPollEvents();
	}
	delete game;
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
