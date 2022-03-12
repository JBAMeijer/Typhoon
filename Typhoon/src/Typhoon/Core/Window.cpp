#include "typhpch.h"
#include "Typhoon/Core/Window.h"

#ifdef TYPH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Typhoon
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef TYPH_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#else
			TYPH_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}