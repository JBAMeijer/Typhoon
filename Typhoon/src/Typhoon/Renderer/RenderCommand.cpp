#include "typhpch.h"
#include "RenderCommand.h"

namespace Typhoon {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}