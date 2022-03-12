#include "typhpch.h"
#include "Typhoon/Core/Input.h"

#ifdef TYPH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Typhoon {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#if defined(TYPH_PLATFORM_WINDOWS)
			return CreateScope<WindowsInput>();
		#else
			TYPH_CORE_ASSERT(false, "Unknown platform!");
			return nullptr; // Should be checked for dist releases
		#endif
	}
}