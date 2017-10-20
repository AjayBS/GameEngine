#pragma once
#include "BitArray.h"

class HeapManager;
class BitArray;

class FixedSizeAllocator
{
public:
	FixedSizeAllocator(size_t sizeBlock, int numBlocks, HeapManager * pDefaultHeap);
	~FixedSizeAllocator();	
	void* alloc();
	void free(void * i_mPointer);
	void SetBitArray(const size_t,const int, HeapManager *);
	BitArray* GetBitArray() const;
	void *pMemoryPointer;
	size_t blockSize;
	size_t numOfBlocks;
private:	
	BitArray *bitArray;

};



