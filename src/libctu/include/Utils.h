#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include "BasicTypes.h"

#if defined(_WIN32)
	#include <memory>
#else
	#include <tr1/memory>
#endif

namespace Utils
{
	#if defined(_WIN32)
	#define SharedPtr std::shared_ptr
	#else
	#define SharedPtr std::tr1::shared_ptr
	#endif

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

	extern bool PromptYesNo(const std::string& question, EColour::Enum colour = EColour::YELLOW);

	extern std::string GetCurrentDir();
	extern std::string GetExecutableDir();

	extern std::string GetConfigFilePath();
	extern std::string GetDefaultTaskListDirectory();

	extern bool FileExists(const std::string& path);
	extern s64 GetFileSize(const std::string& path);
	extern bool TouchFile(const std::string& path);
	extern bool DirectoryExists(const std::string& path);
	extern char PATH_SEPARATOR;

	extern std::string StringTrim(const std::string& str);
	extern std::string StringTrim(const std::string& str, const std::string& trimChars);
	extern std::string StringToLower(const std::string& str);
}

#include "CTUAssert.inl"

#endif
