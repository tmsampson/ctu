#include "Utils.h"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif

namespace Utils
{
	std::string GetDefaultTaskListDirectory()
	{
		#ifdef _WIN32
			char pathResult[MAX_PATH];
			HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathResult);
			if(result != S_OK)
				return "";
			return pathResult;
		#else
			return "foo";
		#endif
	}
}