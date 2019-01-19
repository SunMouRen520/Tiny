#ifndef TINY_CORE_FILESYSTEM_H
#define TINY_CORE_FILESYSTEM_H

#include "Tiny/Types.h"

#include <string>
#include <vector>

namespace Tiny {
	namespace FileSystem {
		std::string GetExePath();

		void SetBaseDir(const std::string& baseDir);
		std::string ReadChar(const std::string& filename);

		std::string GetResourceFullPath(const std::string& path);
	}
}

#endif // !1
