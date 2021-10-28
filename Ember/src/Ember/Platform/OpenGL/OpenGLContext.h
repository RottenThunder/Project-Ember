#pragma once
#include "Ember/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ember
{
	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* WindowHandle;
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}