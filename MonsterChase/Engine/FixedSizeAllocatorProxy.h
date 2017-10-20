#pragma once
class FixedSizeAllocator;
class HeapManager;
namespace FixedSizeAllocatorProxy {
	static FixedSizeAllocator *fixedManagerRef[3];

	FixedSizeAllocator * CreateFixedSizeAllocator(const size_t sizeBlock,const int numBlocks, HeapManager * i_pDefaultHeap);
	FixedSizeAllocator * FindFixedSizeAllocator(const size_t i_size);
	FixedSizeAllocator * FindFixedSizeAllocator(void * i_ptr);
	void CreateHeaps(HeapManager * i_heap);
//	FixedSizeAllocator * FindFixedSizeAllocator(size_t i_size);
}

