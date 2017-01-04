#pragma once
#include "Macros.h"
//void ConsolePrint(const char * i_fmt, ...) {
//
//}
inline void GiveFunctionName(const char* function, ...) {
	va_list ap;
	va_start(ap, function);
	va_end(ap);
	char message[MESSAGE_LENGTH];
	sprintf_s(message, "The function name is %s\n", function);
	PrintToWindowsDebug(message);
}
inline void GetLineAndFile(const int line, const char* file, ...) {
	va_list ap;
	va_start(ap, file);
	va_end(ap);
	char message[MESSAGE_LENGTH];
	sprintf_s(message, "The line number is %d\n", line);
	PrintToWindowsDebug(message);
	sprintf_s(message, "The file is %s\n", file);
	PrintToWindowsDebug(message);
}

inline void GetTimeOfExecution(const char* time, ...) {
	va_list ap;
	va_start(ap, time);
	va_end(ap);
	char message[MESSAGE_LENGTH];
	sprintf_s(message, "The time is %s\n", time);
	PrintToWindowsDebug(message);
}


