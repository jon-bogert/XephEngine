#ifndef __XE_CORE_DEBUGUTIL_H__
#define __XE_CORE_DEBUGUTIL_H__

#include "TimeUtil.h"

#ifdef _DEBUG
#ifdef _CONSOLE
#define LOG(format, ...)\
	do{\
		char buffer[256];\
		int res = snprintf(buffer, std::size(buffer), "{%.3f}:" ##format##"\n", xe::Core::TimeUtil::Time(), __VA_ARGS__);\
        printf(buffer);/
        OutputDebugStringA(buffer);\
	} while(false)
#else // _CONSOLE
#define LOG(format, ...)\
	do{\
		char buffer[256];\
		int res = snprintf(buffer, std::size(buffer), "{%.3f}:" ##format##"\n", xe::Core::TimeUtil::Time(), __VA_ARGS__);\
        OutputDebugStringA(buffer);\
	} while(false)
#endif // _CONSOLE

#define ASSERT(condition, format, ...)\
	do{\
		if(!(condition)){\
			LOG("[ASSERT] %s(%d)\n"##format##, __FILE__, __LINE__, __VA_ARGS__);\
			DebugBreak();\
		}\
	}while(false)

#define XE_PROPERTY(type, name, cap) \
private: \
    type name; \
public: \
    type Get##cap() const { return name; } \
    void Set##cap(type val) { name = val; }\
private:

#define XE_PROP_READONLY(type, name, cap) \
private: \
    type name; \
public: \
    type Get##cap() const { return name; } \
private:

#else
#define LOG(format, ...)
#define ASSERT(condition, format, ...) do{(void)sizeof(condition);} while(false)
#endif // _DEBUG



#endif // !__XE_CORE_DEBUGUTIL_H__
