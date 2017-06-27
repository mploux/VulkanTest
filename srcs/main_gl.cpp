//
// Created by marc on 21/06/17.
//

#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>

using namespace std;

GLFWwindow *createWindow(string title, int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	return (glfwCreateWindow(width, height, title.c_str(), NULL, NULL));
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// glBegin(GL_TRIANGLES);
	// 	glVertex2f(-0.5, -0.5);
	// 	glVertex2f(0.0, 0.5);
	// 	glVertex2f(0.5, -0.5);
	// glEnd();
}

int main()
{
	GLFWwindow	*window = createWindow("Vulkan test", 1280, 720);
	glfwMakeContextCurrent(window);
	double lastTime = 0;
	int frames = 0;
	int ticks = 0;
	while(!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		if (currentTime - lastTime > 1.0 / 60.0)
		{
			ticks++;
			if (ticks % 60 == 0)
			{
				std::cout << "FPS: " << frames << std::endl;
				frames = 0;
			}
			lastTime += 1.0 / 60.0;
		}
		render();
		frames++;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
