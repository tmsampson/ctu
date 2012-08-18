#include "Utils.h"
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <iostream>

#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
	#include <shlwapi.h>
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
	#include <sys/stat.h>
	#include <libgen.h>
	#include <stdarg.h>
	#ifdef __APPLE__
		#include <mach-o/dyld.h>
		#include <stdlib.h>
	#endif
#endif

namespace Utils
{
	// Global variables
	#if defined(_WIN32)
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		char PATH_SEPARATOR = '\\';
	#else
		char PATH_SEPARATOR = '/';
	#endif

	void SetConsoleColour(EColour::Enum colour)
	{
		#if defined(_WIN32)
		static int lookup[] = { FOREGROUND_RED,
		                        FOREGROUND_GREEN,
		                        FOREGROUND_RED | FOREGROUND_GREEN,
		                        FOREGROUND_BLUE
		                      };
		GetConsoleScreenBufferInfo(hstdout, &csbi);
		SetConsoleTextAttribute(hstdout, lookup[colour]);
		#else
			printf("\033[1;%dm", colour + 31);
		#endif
	}

	void ResetConsoleColour()
	{
		#if defined(_WIN32)
			SetConsoleTextAttribute(hstdout, csbi.wAttributes);
		#else
			printf("\033[0m");
		#endif
	}

	void Print(const char* formatString, ...)
	{
		va_list arglist;
		va_start(arglist, formatString);
		vfprintf(stdout, formatString, arglist);
		va_end(arglist);
	}

	void Print(EColour::Enum colour, const char* formatString, ...)
	{
		SetConsoleColour(colour);
		va_list arglist;
		va_start(arglist, formatString);
		vfprintf(stdout, formatString, arglist);
		va_end(arglist);
		ResetConsoleColour();
	}

	void PrintLine(const char* formatString, ...)
	{
		va_list arglist;
		va_start(arglist, formatString);
		std::string fs = std::string(formatString) + "\r\n";
		vfprintf(stdout, fs.c_str(), arglist);
		va_end(arglist);
	}

	void PrintLine(EColour::Enum colour, const char* formatString, ...)
	{
		SetConsoleColour(colour);
		va_list arglist;
		va_start(arglist, formatString);
		std::string fs = std::string(formatString) + "\r\n";
		vfprintf(stdout, fs.c_str(), arglist);
		va_end(arglist);
		ResetConsoleColour();
	}

	bool PromptYesNo(const std::string& question, EColour::Enum colour)
	{
		std::string result;
		bool bValidResult = false;
		while(!bValidResult)
		{
			Utils::PrintLine(Utils::EColour::YELLOW, "%s (y/n): ", question.c_str());
			std::getline(std::cin, result);
			bValidResult = (result == "y"   || result == "n" ||
			                result == "yes" || result == "no");
		}

		return result[0] == 'y';
	}

	std::string GetCurrentDir()
	{
		#if defined(_WIN32)
			#define GetCurrentDirFunc _getcwd
		#else
			#define GetCurrentDirFunc getcwd
		#endif

		static char pathResult[FILENAME_MAX];
		if(GetCurrentDirFunc(pathResult, FILENAME_MAX))
			return pathResult;

		return "";
		#undef GetCurrentDirFunc
	}

	std::string GetExecutableDir()
	{
		static const u32 uSize = FILENAME_MAX;
		static char pResult[uSize];
		#if defined(_WIN32)
			if(GetModuleFileName(NULL, pResult, uSize) &&
			   PathRemoveFileSpec(pResult))
			{
				return pResult;
			}
		#elif defined(__APPLE__)
			static u32 uTemp = uSize;
			if(_NSGetExecutablePath(pResult, &uTemp) == 0)
			{
				static char pResolved[uSize];
				if(realpath(pResult, pResolved) != NULL)
					return dirname(pResolved);
			}
		#else
			if(readlink("/proc/self/exe", pResult, uSize)        != -1 ||
			   readlink("/proc/curproc/file", pResult, uSize)    != -1 ||
			   readlink("/proc/self/path/a.out", pResult, uSize) != -1)
			{
				return dirname(pResult);
			}
		#endif
		return ""; // Unsupported platform
	}

	std::string GetConfigFilePath()
	{
		return Utils::GetExecutableDir() + Utils::PATH_SEPARATOR + "ctu.settings";
	}

	std::string GetDefaultTaskListDirectory()
	{
		#if defined(_WIN32)
			static char pathResult[MAX_PATH];
			HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathResult);
			if(result != S_OK)
				return "";
			return pathResult;
		#else
			struct passwd *pw = getpwuid(getuid());
			return pw->pw_dir;
		#endif
	}

	bool FileExists(const std::string& path)
	{
		return std::ifstream(path.c_str()).good();
	}

	s64 GetFileSize(const std::string& path)
	{
		std::ifstream fstream(path.c_str());
		fstream.seekg(0, std::ios::end);
		return fstream.tellg();
	}

	bool TouchFile(const std::string& path)
	{
		if(FileExists(path))
			return true;

		std::ofstream touch(path.c_str());
		return touch.is_open();
	}

	bool DirectoryExists(const std::string& path)
	{
		#if defined(_WIN32)
			s32 result = GetFileAttributes(path.c_str());
			return (result != INVALID_FILE_ATTRIBUTES &&
			        result & FILE_ATTRIBUTE_DIRECTORY);
		#else
			struct stat sb;
			return (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
		#endif
	}

	std::string StringTrim(const std::string& str)
	{
		u32 endMarker = str.size();
		if (!endMarker)
			return str; // Early out

		// Move endMarker back?
		for(; endMarker > 0 && str[endMarker - 1] == ' '; --endMarker);

		// Return trimmed string
		return str.substr(0, endMarker);
	}

	std::string StringTrim(const std::string& str, const std::string& trimChars)
	{
		u32 endMarker = str.size();
		if (!endMarker || !trimChars.size())
			return str; // Early out

		// Move endMarker back?
		for (; endMarker > 0; --endMarker)
		{
			if(trimChars.find(str[endMarker - 1]) == std::string::npos)
				break;
		}

		// Return trimmed string
		return str.substr(0, endMarker);
	}

	std::string StringToLower(const std::string& str)
	{
		std::string copy = str;
		std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
		return copy;
	}

	
}
