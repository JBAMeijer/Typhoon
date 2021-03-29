#include "typhpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Typhoon {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}