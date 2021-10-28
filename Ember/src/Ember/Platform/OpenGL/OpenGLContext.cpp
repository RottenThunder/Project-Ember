#include "empch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ember
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: WindowHandle(windowHandle)
	{
		EM_FATAL_ASSERT(windowHandle, "Window Handle is Null!!!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(WindowHandle);
		int32_t gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EM_FATAL_ASSERT(gladStatus, "Failed to Initialize Glad!!!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
	}
}