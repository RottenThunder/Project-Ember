#include "empch.h"
#include <GLFW/glfw3.h>
#include "Application.h"

namespace Ember
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		bool successfulInit = glfwInit();
		EM_FATAL_ASSERT(successfulInit, "Didn't Initialize GLFW!!!");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(1280, 720, "Ember Engine", NULL, NULL);

		EM_FATAL_ASSERT(window, "Window Object == NULL!!!");

		glfwMakeContextCurrent(window);

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.9412f, 0.3686f, 0.1059f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwDestroyWindow(window);

		glfwTerminate();
	}
}