#include "empch.h"
#include "RenderCommand.h"
#include "Ember/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ember
{
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI;
}