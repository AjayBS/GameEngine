#pragma once
#ifndef __ENGINE_TYPES_H 
#define __ENGINE_TYPES_H
#include<stdint.h>

#ifdef _WIN64
typedef uint64_t myint_t;
#else 
typedef uint32_t myint_t;
#endif 
#endif // __ENGINE_TYPES_H