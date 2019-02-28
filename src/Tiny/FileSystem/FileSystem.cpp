#include "Tiny/FileSystem/FileSystem.h"

#include "Tiny/Core/Service.h"

#include <fstream>

namespace Tiny { namespace FileSystem {
	static std::string _baseDir = "";

#ifdef WIN32
#include <windows.h>
	std::string GetExePath()
	{
		char result[MAX_PATH];
		std::string exePath = std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
		std::size_t index = exePath.find_last_of("\\");
		return exePath.substr(0, index + 1);
	}
#else 
#ifdef LINUX
#include <limits.h>
#include <unistd.h>

	std::string GetExePath()
	{
		char result[PATH_MAX];
		ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
		return std::string(result, (count > 0) ? count : 0);
	}
#endif
#endif

	void SetBaseDir(const std::string& baseDir) {
		_baseDir = baseDir;
	}

	std::string GetResourceFullPath(const std::string& path) {
		return _baseDir + path;
	}

	std::ifstream OpenFile(const std::string& filename, std::ios_base::openmode mode) {
		std::string fullfileName;
		fullfileName.append(_baseDir + filename);
		std::ifstream file(fullfileName, mode);

		if (!file.is_open())
			throw std::invalid_argument(("File" + filename + " open failed!"));

		return file;
	}

	std::string ReadChar(const std::string& filename) {
		std::string content;

		try {
			std::ifstream file = OpenFile(filename, std::ios::ate | std::ios::binary);
			uint32_t len = static_cast<uint32_t>(file.tellg());
			content.resize(len + 1);
			file.seekg(0, std::ios::beg);
			file.read((char*)&content[0], len);
			file.close();
		}
		catch(std::exception e){
			Tiny::Service::Log(). E("Binary Read failed:{}", e.what());
		}
		return content;
	}
} }