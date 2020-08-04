#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Luci/Debug/Log.h"
#include "Luci/Debug/Instrumentor.h"

#ifdef LUCI_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // LUCI_PLATFORM_WINDOWS
