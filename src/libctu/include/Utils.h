#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "BasicTypes.h"

namespace Utils
{
	extern std::string GetCurrentDir();
	extern std::string GetExecutableDir();

	extern std::string GetConfigFilePath();
	extern std::string GetDefaultTaskListDirectory();

	extern bool FileExists(const std::string& path);
	extern s64 GetFileSize(const std::string& path);
	extern bool TouchFile(const std::string& path);
	extern bool DirectoryExists(const std::string& path);
	extern char PATH_SEPARATOR;
}

#endif