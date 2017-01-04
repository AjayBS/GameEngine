#ifndef __ALLOCATORS_H
#define __ALLOCATORS_H

#include "HeapManager.h"

// standard new / delete
void * operator new(size_t i_size);
void operator delete(void * i_ptr);

// standard array new / delete
void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);

// custom alignment allocators
enum NewAlignment
{
	NEW_ALIGN_DEFAULT,
	NEW_ALIGN_16 = 16,
	NEW_ALIGN_32 = 32
};

void * operator new(size_t i_size, NewAlignment i_align);
void operator delete(void * i_ptr, NewAlignment i_align);

// tracking allocators
// used by TRACK_NEW
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line);
void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line);

#ifdef _DEBUG
#define TRACK_NEW (__FILE__,__LINE__)
#else
#define TRACK_NEW
#endif

HeapManager * getDefaultHeap();

// heap allocators
// i_pHeap = NULL means grab the default HeapManager
void * operator new(size_t i_size, HeapManager * i_pHeap);
void operator delete(void * i_ptr, HeapManager * i_pHeap);

void * operator new(size_t i_size, HeapManager * i_pHeap, unsigned int i_align);
void operator delete(void * i_ptr, HeapManager * i_pHeap, unsigned int i_align);

#endif // __ALLOCATORS_H