#include "Utils.h"

#ifdef _WIN32
	#include <windows.h>
	#include <shlobj.h>
#else
	#include <unistd.h>
	#include <sys/types.h>
	#include <pwd.h>
#endif

namespace Utils
{
	std::string GetDefaultTaskListDirectory()
	{
		#if defined(_WIN32)
			char pathResult[MAX_PATH];
			HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathResult);
			if(result != S_OK)
				return "";
			return pathResult;
		#else
			struct passwd *pw = getpwuid(getuid());
			return pw->pw_dir;
		#endif
	}
}