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