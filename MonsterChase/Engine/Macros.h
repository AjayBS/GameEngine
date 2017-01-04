#pragma once
#if defined(_DEBUG)
#define TRACK_NEW (__FILE__,__LINE__)
#define assert(cond) if((cond)) __debugbreak();
#else
#define TRACK_NEW
#define assert(cond)    void(0);
#endif // defined(BUILD_DEBUG)

const int DEFAULT_SIZE_BLOCK = 0;
const int DEFAULT_ALIGNMENT = 4;
const int VALUE_ONE = 1;
const int VALUE_ZERO = 0;
const int MESSAGE_LENGTH = 500;

const int MAX_POSITION_VALUE = 100;
const int MIN_POSITION_VALUE = 0;

const int NAME_LENGTH = 100;
const int INITIAL_DESCRIPTOR_SIZE = 120;
const int INITIAL_HEAP_SIZE = 1024 * 1024;
