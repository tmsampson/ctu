#include "Utils.h"

#include <stdio.h>
#include <fstream>

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
	#ifdef __APPLE__
		#include <mach-o/dyld.h>
		#include <stdlib.h>
	#endif
#endif

namespace Utils
{
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
		#else
			#if defined(__APPLE__)
				static u32 uTemp = uSize;
				if(_NSGetExecutablePath(pResult, &uTemp) == 0)
				{
					static char pResolved[uSize];
					if(realpath(pResult, pResolved) != NULL)
						return pResolved;
				}
			#else
			if(readlink("/proc/self/exe", pResult, uSize)        != -1 ||
			   readlink("/proc/curproc/file", pResult, uSize)    != -1 ||
			   readlink("/proc/self/path/a.out", pResult, uSize) != -1)
			{
				return dirname(pResult);
			}
			#endif
		#endif
		return ""; // Unsupported platform
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
		return std::ifstream(path.c_str()).is_open();
	}

	s64 GetFileSize(const std::string& path)
	{
		std::ifstream fstream(path.c_str());
		fstream.seekg(0, std::ios::end);
		return fstream.tellg();
	}

	bool DirectoryExists(const std::string& path)
	{
		#if defined(_WIN32)
			return GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES;
		#else
			struct stat sb;
			return (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode));
		#endif
	}
}
