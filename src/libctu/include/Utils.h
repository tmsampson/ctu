#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <memory>
#include "BasicTypes.h"
#if !defined(_WIN32)
	#include <tr1/memory>
	#include <assert.h>
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

	inline void Assert(bool bCondition, const std::string& file, const std::string& function, u32 uLine, const std::string& message)
	{
		if(bCondition)
			return;

		Utils::PrintLine(Utils::EColour::RED, "***************************************************");
		Utils::PrintLine(Utils::EColour::RED, " A S S E R T   F A I L E D");
		Utils::PrintLine(Utils::EColour::RED, "***************************************************");
		if(message.size())
			Utils::PrintLine(Utils::EColour::RED, "  Message: %s", message.c_str());
		Utils::PrintLine(Utils::EColour::RED, "     File: %s", file.c_str());
		Utils::PrintLine(Utils::EColour::RED, " Function: %s", function.c_str());
		Utils::PrintLine(Utils::EColour::RED, "     Line: %d", uLine);
		Utils::PrintLine(Utils::EColour::RED, "***************************************************");
		#if defined(_WIN32)
			__asm
			{
				int 4;
			}
		#else
			assert(false);
		#endif
	}

	#if defined(NDEBUG)
		#define CPU_ASSERT(expression, message) ((void)0)
		#define CPU_ASSERT_ONLY(expression) ((void)0)
	#else
		#define CPU_ASSERT(expression, message) Utils::Assert((expression), __FILE__, __FUNCTION__, __LINE__, (message))
		#define CPU_ASSERT_ONLY(expression) Utils::Assert((expression), __FILE__, __FUNCTION__, __LINE__, "")
	#endif
}

#endif
