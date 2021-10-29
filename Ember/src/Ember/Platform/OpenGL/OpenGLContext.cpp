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

		EM_LOG_WARN("Vendor: {0}", glGetString(GL_VENDOR));
		EM_LOG_WARN("GPU: {0}", glGetString(GL_RENDERER));
		EM_LOG_WARN("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
	}
}