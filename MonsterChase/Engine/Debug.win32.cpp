#include<stdio.h>
#include "Debug.h"
#include"windows.h"
#define STR2(X) #X
#define STR(X) STR2(X)

Debug::Debug()
{
}


Debug::~Debug()
{
}

void PrintToWindowsDebug(const char *msg) {
	OutputDebugStringA(msg);
}

void ConsolePrint(const char *i_pFmt, ...) {
	const int MESSAGE_BUFFER_SIZE = 100;
	char msgbuff[MESSAGE_BUFFER_SIZE];
	va_list args;
	va_start(args, i_pFmt);
	vsprintf_s(msgbuff, i_pFmt, args);
	va_end(args);
	OutputDebugStringA(msgbuff);
}