#ifndef TINY_FILESYSTEM_UTILITY_H 
#define TINY_FILESYSTEM_UTILITY_H

#include <string>

namespace Tiny { namespace FileSystem {

	std::string FileType(const std::string& fileName) {
		std::size_t index = fileName.rfind(".");
		if (index != std::string::npos){
			return fileName.substr(index);
		}
		return "";
	}
} }

#endif