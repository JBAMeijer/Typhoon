#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <sstream>

#include <filesystem>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Typhoon/Core/Log.h"
#include "Typhoon/Debug/Instrumentor.h"

#ifdef TYPH_PLATFORM_WINDOWS
	#include <Windows.h>
#endif