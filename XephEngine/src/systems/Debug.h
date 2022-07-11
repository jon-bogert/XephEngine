#pragma once

namespace xe
{
	namespace Debug
	{
		int LogInfo(const char* fmt, ...);
		int LogWarn(const char* fmt, ...);
		int LogErr(const char* fmt, ...);
	}
}

