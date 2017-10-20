#include "FixedSizeAllocatorProxy.h"
#include "FixedSizeAllocator.h"

namespace FixedSizeAllocatorProxy {
	using namespace HeapManagerProxy;
		FixedSizeAllocator * CreateFixedSizeAllocator(const size_t sizeBlock,const int numBlocks, HeapManager * i_pDefaultHeap)
		{
			FixedSizeAllocator *fsa = reinterpret_cast<FixedSizeAllocator *>(HeapManagerProxy::alloc(i_pDefaultHeap, sizeBlock * numBlocks, 4));
			fsa->pMemoryPointer = i_pDefaultHeap->pOutstandingAllocationList->m_pMemoryPointer;
			fsa->SetBitArray(sizeBlock, numBlocks, i_pDefaultHeap);
			return fsa;
		}

		void CreateHeaps(HeapManager * i_heap)
		{
			i_heap->FSASizes[0].sizeBlock = 8;
			i_heap->FSASizes[0].numBlocks = 24;

			i_heap->FSASizes[1].sizeBlock = 16;
			i_heap->FSASizes[1].numBlocks = 24;

			i_heap->FSASizes[2].sizeBlock = 32;
			i_heap->FSASizes[2].numBlocks = 24;

			for (unsigned int i = 0; i < MAX_NUMBER_OF_FSA; i++)
				fixedManagerRef[i] = CreateFixedSizeAllocator(i_heap->FSASizes[i].sizeBlock, i_heap->FSASizes[i].numBlocks, i_heap);
		}

		FixedSizeAllocator * FindFixedSizeAllocator(const size_t i_size){
			//FixedSizeAllocator * best = fixedManagerRef[0]->GetBitArray()->GetNumberOfBits();
				if (i_size < 8)
					return fixedManagerRef[0];
				else if(i_size>=8 && i_size<16)
					return fixedManagerRef[1];
				else if(i_size>=16 && i_size<32) 
					return fixedManagerRef[2];
				else
					return nullptr;
		}
		FixedSizeAllocator * FindFixedSizeAllocator(void * i_ptr)
		{
			for (int i = 0; i < MAX_NUMBER_OF_FSA; i++) {
				if (i_ptr >= fixedManagerRef[i]->pMemoryPointer && i_ptr < (reinterpret_cast<uint8_t *>(fixedManagerRef[i]->pMemoryPointer) + (fixedManagerRef[i]->blockSize * fixedManagerRef[i]->numOfBlocks))) {
					
					return fixedManagerRef[i];
				}
			}
			return nullptr;
		}
}
