#include "FixedSizeAllocator.h"


FixedSizeAllocator::FixedSizeAllocator(size_t sizeBlock, int numBlocks, HeapManager * pDefaultHeap)
{
	//CreateFixedSizeAllocator(sizeBlock, numBlocks, pDefaultHeap);
}


FixedSizeAllocator::~FixedSizeAllocator()
{
	if (bitArray->GetFirstClearBit() != GARBAGE_RETURN_VALUE_OF_BIT)
	{
		// Oh no! We have an outstanding allocation
		//assert(true);
		DEBUG_CONSOLE("We have some memory occupied. Please free them!");
	}
}

void * FixedSizeAllocator::alloc()
{
	size_t i_firstAvailable = -1;
	i_firstAvailable = bitArray->GetFirstSetBit();
	if (i_firstAvailable != -1) {
		bitArray->ClearBit(i_firstAvailable);
		return (void *)((uintptr_t)pMemoryPointer + (i_firstAvailable * blockSize));
	}
	else {
		return nullptr;
	}

}

void FixedSizeAllocator::free(void * i_mPointer)
{
	//bool a;
	size_t resetBlock;
	resetBlock = size_t((reinterpret_cast<uintptr_t>(i_mPointer) - reinterpret_cast<uintptr_t>(pMemoryPointer)) / blockSize);
	if (bitArray->IsBitClear(resetBlock)) {
		//a = bitArray->IsBitClear(resetBlock);
		bitArray->SetBit(resetBlock);
		//a = bitArray->IsBitClear(resetBlock);
	}
	else {
		assert(true);
	}
	//i_mPointer = (uintptr_t)pMemoryPointer + (resetBlock * blockSize);
}

void FixedSizeAllocator::SetBitArray(const size_t i_sizeBlock,const int i_numBlocks, HeapManager * i_pManager)
{
	blockSize = i_sizeBlock;
	numOfBlocks = i_numBlocks;
	bitArray = reinterpret_cast<BitArray *>(HeapManagerProxy::alloc(i_pManager, i_numBlocks, 4));// new BitArray(numBlocks, i_pManager);
	bitArray->Create(i_numBlocks, bitArray, true);
}

BitArray * FixedSizeAllocator::GetBitArray() const
{
	return bitArray;
}



