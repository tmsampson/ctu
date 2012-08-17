#if defined(_WIN32)
	#include <intrin.h>
#endif

namespace Utils
{
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
			 __debugbreak();  // MSVC intrinsic
		#else
			__builtin_trap(); // GCC 'built-in'
		#endif
	}
}

#if defined(NDEBUG)
	#define CTU_ASSERT(expression, message) ((void)0)
	#define CTU_ASSERT_ONLY(expression) ((void)0)
#else
	#define CTU_ASSERT(expression, message) Utils::Assert((expression), __FILE__, __FUNCTION__, __LINE__, (message))
	#define CTU_ASSERT_ONLY(expression) Utils::Assert((expression), __FILE__, __FUNCTION__, __LINE__, "")
#endif