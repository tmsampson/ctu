#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "BasicTypes.h"

namespace Utils
{
	namespace EColour
	{
		enum Enum
		{
			RED    = 0,
			GREEN  = 1,
			YELLOW = 2,
			BLUE   = 3,
		};
	}

	extern void Print(const char* formatString, ...);
	extern void Print(EColour::Enum colour, const char* formatString, ...);
	extern void PrintLine(const char* formatString, ...);
	extern void PrintLine(EColour::Enum colour, const char* formatString, ...);

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