#include "typhpch.h"
#include "Typhoon/Renderer/RenderCommand.h"

namespace Typhoon {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}