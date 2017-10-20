#pragma once
#include <stdio.h>
#include<stdarg.h>
class Debug
{
public:
	Debug();
	~Debug();

};

inline void GiveFunctionName(const char* function, ...);
inline void GetLineAndFile(const int line, const char* file, ...);
inline void GetTimeOfExecution(const char* time, ...);
void PrintToWindowsDebug(const char *msg);
void ConsolePrint(const char *i_pName, ...);

#if defined(_DEBUG)
#define DEBUG_FUNCTION GiveFunctionName(__FUNCTION__);
#define DEBUG_LINE_FILE GetLineAndFile(__LINE__,__FILE__);
#define DEBUG_TIMESTAMP GetTimeOfExecution(__TIMESTAMP__);
#define _GUARDBAND
#define DEBUG_LOG PrintToWindowsDebug;
#define DEBUG_CONSOLE(message,...) ConsolePrint(message,##__VA_ARGS__);
//#define ConsolePrint ConsolePrint;
#else
#define DEBUG_LINE_FILE void(0);
#define DEBUG_LOCATION void(0);
#define DEBUG_TIMESTAMP void(0);
#define DEBUG_FUNCTION void(0);
#define DEBUG_CONSOLE(message,...) void(0);
#endif

#include "Debug-inl.h"