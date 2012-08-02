#include "Utils.h"

#ifdef _WIN32
	#include <windows.h>
	#include <fstream>
	#include <shlobj.h>
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
	#include <sys/stat.h>
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
		if(GetCurrentDirFunc(pathResult, sizeof(pathResult) / sizeof(TCHAR)))
			return pathResult;

		return "";
		#undef GetCurrentDirFunc
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

	bool DirectoryExists(const std::string& path)
	{
		#if defined(_WIN32)
			return GetFileAttributes(path.c_str()) != INVALID_FILE_ATTRIBUTES;
		#else
			struct stat sb;
			return (stat(pathname, &sb) == 0 && S_ISDIR(sb.st_mode));
		#endif
	}
}