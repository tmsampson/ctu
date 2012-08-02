#ifndef UTILS_H_
#define UTILS_H_

#include <string>

namespace Utils
{
	extern std::string GetCurrentDir();
	extern std::string GetDefaultTaskListDirectory();

	extern bool FileExists(const std::string& path);
	extern bool DirectoryExists(const std::string& path);
}

#endif