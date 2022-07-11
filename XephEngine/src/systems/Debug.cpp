#include "Debug.h"
#include "../Libraries.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "windows.h"
//#include <chrono>

#pragma warning(disable : 4996)

int xe::Debug::LogInfo(const char* fmt, ...)
{
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << "[" << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "]";

	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	std::cout << "[INFO]: " << buffer << std::endl;
	return rc;
}

int xe::Debug::LogWarn(const char* fmt, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << "[" << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "]";

	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	std::cout << "[WARN]: " << buffer << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return rc;
}

int xe::Debug::LogErr(const char* fmt, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << "[" << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "]";

	char buffer[4096];
	va_list args;
	va_start(args, fmt);
	int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	std::cout << "[ERROR]: " << buffer << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return rc;
}
