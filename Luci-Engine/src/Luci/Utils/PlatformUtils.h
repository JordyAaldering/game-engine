#pragma once

#include <string>

namespace Luci {

	class FileDialogs {
	public:
		// return empty strings when cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}
