#include "HeapManager.h"

HeapManager::HeapManager()
{

}


HeapManager::~HeapManager()
{
}

namespace HeapManagerProxy {
	HeapManager* CreateHeapManager(void *pHeapMemory, size_t sizeHeap, const myint_t numDescriptors) {
		
		HeapManager * heapManager = reinterpret_cast<HeapManager *>(pHeapMemory);
		pHeapMemory=reinterpret_cast<uint8_t *>(pHeapMemory) + sizeof(HeapManager);
		sizeHeap -= sizeof(HeapManager);
		//new(pHeapManager) PlayerController();
		//HeapManager *heapManager = new (pHeapManagerMem) HeapManager();

		heapManager->pFreeMemoryList = pHeapMemory;
		heapManager->heapSize = sizeHeap;
		heapManager->numDescriptors = numDescriptors;
		heapManager->descriptorStorage = numDescriptors * sizeof(BlockDescriptor);

		heapManager->pFreeDescriptorList = reinterpret_cast<BlockDescriptor*>(reinterpret_cast<uintptr_t>(heapManager->pFreeMemoryList) + sizeHeap) - heapManager->descriptorStorage;
		heapManager->pFreeDescriptorList->m_pNext = heapManager->pFreeDescriptorList + sizeof(BlockDescriptor);
		heapManager->pFreeDescriptorList->m_pPrevious = nullptr;
		heapManager->pFreeDescriptorList->m_sizeBlock = DEFAULT_SIZE_BLOCK;
		size_t currentBlockDescriptor = VALUE_ONE;
		while (true)
		{
			if (currentBlockDescriptor == heapManager->numDescriptors) {
				break;
			}
			heapManager->pFreeDescriptorList = heapManager->pFreeDescriptorList->m_pNext;
			if (currentBlockDescriptor == heapManager->numDescriptors - VALUE_ONE) {
				heapManager->pFreeDescriptorList->m_pNext = nullptr;
			}
			else {
				heapManager->pFreeDescriptorList->m_pNext = heapManager->pFreeDescriptorList + sizeof(BlockDescriptor);
			}
			heapManager->pFreeDescriptorList->m_pPrevious = heapManager->pFreeDescriptorList - sizeof(BlockDescriptor);
			heapManager->pFreeDescriptorList->m_sizeBlock = DEFAULT_SIZE_BLOCK;
			currentBlockDescriptor++;
		}
		heapManager->pFreeDescriptorList->m_pMemoryPointer = heapManager->pFreeMemoryList;
		heapManager->pFreeDescriptorList->m_sizeBlock = sizeHeap - (heapManager->numDescriptors * sizeof(BlockDescriptor));
		heapManager->pOutstandingAllocationList = nullptr;
		return heapManager;

	}

	void* alloc(HeapManager *i_pManager, size_t i_size, const myint_t alignment) {

		//Get the size requested by the user including guardbands.
		size_t iRequestedBytes = i_size + alignment;
		//size_t availableMemory = TOTAL_SIZE - (NO_OF_DESCRIPTORS * sizeof(BlockDescriptor)) - ((char *)pFreeMemoryList - (char *)pFreeDescriptorList->m_pMemoryPointer)-iRequestedBytes;
	/*	if (i_pManager->pFreeDescriptorList == nullptr) {
			printf_s("kllll");
		}*/
		
		size_t availableMemory = i_pManager->GetAvailableSize(i_pManager);

		if (i_size == 0) {
			assert(true);
		}

		if (iRequestedBytes > (size_t)availableMemory) {
			assert(true);
		}

		int allocatedListCount = 0;
		BlockDescriptor *tempAllocator = i_pManager->pOutstandingAllocationList;
		do {
			if (tempAllocator == nullptr) {
				break;
			}
			allocatedListCount++;
			tempAllocator = tempAllocator->m_pNext;
		} while (tempAllocator != nullptr);

		if (allocatedListCount >= (int)i_pManager->numDescriptors) {
			assert(true);
		}

		// Garbage Collector
		while (iRequestedBytes > i_pManager->pFreeDescriptorList->m_sizeBlock) {
			i_pManager->pFreeDescriptorList=i_pManager->pFreeDescriptorList->m_pPrevious;
			//GarbageCollect(i_pManager);
		}

		if (i_pManager->pOutstandingAllocationList != nullptr) {
			if (i_pManager->pFreeDescriptorList->m_pPrevious != nullptr) {
				BlockDescriptor *tempDescriptor = i_pManager->pOutstandingAllocationList;
				i_pManager->pFreeDescriptorList = i_pManager->pFreeDescriptorList->m_pPrevious;
				tempDescriptor->m_pNext = i_pManager->pFreeDescriptorList->m_pNext;
				tempDescriptor->m_pNext->m_pPrevious = i_pManager->pOutstandingAllocationList;
				tempDescriptor->m_pNext->m_pNext = nullptr;
				tempDescriptor->m_pNext->m_sizeBlock = iRequestedBytes;
				//pOutstandingAllocationList->m_pNext = tempDescriptor;
				i_pManager->pFreeDescriptorList->m_pNext = nullptr;
				i_pManager->pOutstandingAllocationList = i_pManager->pOutstandingAllocationList->m_pNext;
			}
			else {
				BlockDescriptor *tempDescriptor = i_pManager->pOutstandingAllocationList;

			}
		}
		else {
			BlockDescriptor *tempDescriptor = i_pManager->pOutstandingAllocationList;
			i_pManager->pFreeDescriptorList = i_pManager->pFreeDescriptorList->m_pPrevious;
			i_pManager->pOutstandingAllocationList = i_pManager->pFreeDescriptorList->m_pNext;
			i_pManager->pOutstandingAllocationList->m_sizeBlock = iRequestedBytes;
			i_pManager->pOutstandingAllocationList->m_pNext = nullptr;
			i_pManager->pOutstandingAllocationList->m_pPrevious = nullptr;
			i_pManager->pFreeDescriptorList->m_pNext = nullptr;
		}

		//pFreeMemoryList =(void *)( pFreeMemoryList + pFreeDescriptorList->m_sizeBlock);
		BlockDescriptor *tempDescriptor = i_pManager->pFreeDescriptorList;
		// Update the memory pointer to point to the next remaining memory
		i_pManager->pFreeDescriptorList->m_pMemoryPointer = reinterpret_cast<void *>(reinterpret_cast<uintptr_t>(i_pManager->pOutstandingAllocationList->m_pMemoryPointer) + i_pManager->pOutstandingAllocationList->m_sizeBlock);
		// Update the size to the remaining memory and assign to the next free descriptor		
		i_pManager->pFreeDescriptorList->m_sizeBlock = i_pManager->GetAvailableSize(i_pManager);
		// The pointer of the previous free descriptor one is updated.
		//pFreeDescriptorList->m_pNext = nullptr;
		return i_pManager->pOutstandingAllocationList->m_pMemoryPointer;
	}

	void free(HeapManager *i_pManager, void* deallocation_pointer) {
		BlockDescriptor *tempMemoryAllocator = i_pManager->pOutstandingAllocationList;
		while (true) {
			// Check if the outstanding list is null, if yes return false.
			if (tempMemoryAllocator == nullptr) {
				break;
			}
			// Iterate through the outstanding list
			else if (tempMemoryAllocator->m_pMemoryPointer == deallocation_pointer) {
				BlockDescriptor *swapPreviousFreeList = i_pManager->pFreeDescriptorList->m_pPrevious;
				size_t availableMemory = i_pManager->GetAvailableSize(i_pManager);
				if (tempMemoryAllocator->m_pNext == nullptr && tempMemoryAllocator->m_pPrevious == nullptr) {
					// Get the memory of 
					//if(tempMemoryAllocator)
					//tempMemoryAllocator->m_pPrevious = 
					AddFreedBlockToTheFreeDescriptorList(i_pManager, tempMemoryAllocator);
					i_pManager->pOutstandingAllocationList = nullptr;
					//tempMemoryAllocator->m_pPrevious->m_pNext = nullptr;
				}
				// If it is the first element in the list. make previous of second one null
				else if (tempMemoryAllocator->m_pPrevious == nullptr && tempMemoryAllocator->m_pNext != nullptr) {
					tempMemoryAllocator->m_pNext->m_pPrevious = nullptr;
					i_pManager->pOutstandingAllocationList = tempMemoryAllocator->m_pNext;
					AddFreedBlockToTheFreeDescriptorList(i_pManager, tempMemoryAllocator);
					//pOutstandingAllocationList->m_pNext = nullptr;
				}
				// If it is the last element in linked list
				else if (tempMemoryAllocator->m_pPrevious != nullptr && tempMemoryAllocator->m_pNext == nullptr) {
					tempMemoryAllocator->m_pPrevious->m_pNext = nullptr;
					i_pManager->pOutstandingAllocationList = tempMemoryAllocator->m_pPrevious;
					AddFreedBlockToTheFreeDescriptorList(i_pManager, tempMemoryAllocator);
					//tempMemoryAllocator->m_pNext->m_pPrevious = tempMemoryAllocator->m_pPrevious;
				}
				// If it is the middle element
				else {
					tempMemoryAllocator->m_pPrevious->m_pNext = tempMemoryAllocator->m_pNext;
					tempMemoryAllocator->m_pNext->m_pPrevious = tempMemoryAllocator->m_pPrevious;
					AddFreedBlockToTheFreeDescriptorList(i_pManager, tempMemoryAllocator);
				}
				break;
			}
			tempMemoryAllocator = tempMemoryAllocator->m_pPrevious;

		}
		while(i_pManager->pOutstandingAllocationList != nullptr && i_pManager->pOutstandingAllocationList->m_pNext != nullptr)
		i_pManager->pOutstandingAllocationList = i_pManager->pOutstandingAllocationList->m_pNext;
		i_pManager->allocatedCount -= VALUE_ONE;
		//return;
	}

	void AddFreedBlockToTheFreeDescriptorList(HeapManager *i_pManager, BlockDescriptor* freedBlock) {
		// If it is the first element to be freed and freed element lies in the first of the descriptor list
		if (i_pManager->pFreeDescriptorList->m_pNext == nullptr && freedBlock > i_pManager->pFreeDescriptorList) {
			freedBlock->m_pNext = nullptr;
			//pFreeDescriptorList->m_pNext = freedBlock;
			freedBlock->m_pPrevious = i_pManager->pFreeDescriptorList;
			freedBlock->m_pPrevious->m_pNext = freedBlock;
			i_pManager->pFreeDescriptorList = freedBlock;
			//freedBlock->m_sizeBlock = sizeof(BlockDescriptor);
			//freedBlock->m_pMemoryPointer = pFreeDescriptorList->m_pMemoryPointer;
		}
		else if (i_pManager->pFreeDescriptorList->m_pNext == nullptr && freedBlock < i_pManager->pFreeDescriptorList) {
			BlockDescriptor *tempBlock = i_pManager->pFreeDescriptorList;
			//freedBlock->m_pNext = tempBlock;
			//tempBlock->m_pPrevious = freedBlock;
			while (1) {
				if (freedBlock < tempBlock) {
					freedBlock->m_pNext = tempBlock;
				}
				if (freedBlock > tempBlock) {
					freedBlock->m_pPrevious = tempBlock;
					tempBlock->m_pNext->m_pPrevious = freedBlock;
					tempBlock->m_pNext = freedBlock;
					break;
				}
				tempBlock = tempBlock->m_pPrevious;
			}
			//pFreeDescriptorList->m_pPrevious = freedBlock;

		}
		else if (i_pManager->pFreeDescriptorList->m_pPrevious == nullptr) {

		}
		//pFreeDescriptorList->m_pPrevious = freedBlock;
		ResetFreeDescriptor(i_pManager);
	}

	void ResetFreeDescriptor(HeapManager *i_pManager)
	{
		while (i_pManager->pFreeDescriptorList->m_pNext != nullptr) {
			i_pManager->pFreeDescriptorList = i_pManager->pFreeDescriptorList->m_pNext;
		}
	}
	

	void GarbageCollect(HeapManager *i_pManager) {
		//ResetFreeDescriptor();

		BlockDescriptor * pPreviousBlock = i_pManager->pFreeDescriptorList->m_pPrevious;
		// if this block abuts the following block combine them
		while (true) {
			if ((reinterpret_cast<uintptr_t>(i_pManager->pFreeDescriptorList->m_pMemoryPointer) + i_pManager->pFreeDescriptorList->m_sizeBlock) == reinterpret_cast<uintptr_t>(pPreviousBlock->m_pMemoryPointer)) {
				Combine(i_pManager->pFreeDescriptorList, pPreviousBlock);
			}
			else {
				if (i_pManager->pFreeDescriptorList->m_pPrevious) {
					break;
				}
				i_pManager->pFreeDescriptorList = i_pManager->pFreeDescriptorList->m_pPrevious;
			}
		}
		
		ResetFreeDescriptor(i_pManager);
		/*BlockDescriptor * pPreviousBlock = pFreeDescriptorList->m_pPrevious;
		if (pPreviousBlock != NULL) {
		pFreeDescriptorList->m_pPrevious->m_sizeBlock = pFreeDescriptorList->m_sizeBlock + pPreviousBlock->m_sizeBlock;
		pFreeDescriptorList = pPreviousBlock;
		pFreeDescriptorList->m_pNext = nullptr;
		}
		else {
		assert(true);
		}*/
	}

	void Combine(BlockDescriptor * presentBlock, BlockDescriptor * previousBlock)
	{
		if (presentBlock->m_pMemoryPointer<previousBlock->m_pMemoryPointer) {
			presentBlock->m_sizeBlock = presentBlock->m_sizeBlock + previousBlock->m_sizeBlock;
		}
		else {
			presentBlock->m_pMemoryPointer = previousBlock->m_pMemoryPointer;
			presentBlock->m_sizeBlock = presentBlock->m_sizeBlock + previousBlock->m_sizeBlock;
		}
	
	}
	

	


	HeapManager * GetHeapManager()
	{
		return heapManagerRef;
	}

	void SetHeapManager(HeapManager *heap)
	{
		heapManagerRef = heap;
	}
	
}
using namespace HeapManagerProxy;

//void * operator new(size_t i_size, HeapManager * pHeap)
//{
//	using namespace HeapManagerProxy;
//	/*assert(pHeap != NULL);
//	assert(IsPowerOfTwo(i_alignment));
//*/
//	return alloc(pHeap, i_size, 4);
//}
//
//void operator delete(void * i_ptr)
//{
//	using namespace HeapManagerProxy;
//	if (i_ptr)
//		free(heapManagerRef, i_ptr);
//}

// standard new & delete
void * operator new(size_t i_size)
{
	//DEBUG_PRINT("Calling new( size_t ) with ( %Iu ).\n", i_size);

	return alloc(heapManagerRef, i_size, DEFAULT_ALIGNMENT);
}

void operator delete(void * i_ptr)
{
	//DEBUG_PRINT("Calling delete( void * ) with ( %" PRIxPTR " ).\n", i_ptr);
	if (i_ptr)
		free(heapManagerRef, i_ptr);
}

void * operator new(size_t i_size, HeapManager * i_pHeap)
{
	//DEBUG_PRINT("Calling new( size_t, HeapManager * ) with ( %Iu, %" PRIxPTR ").\n", i_size, i_pHeap);

	/*if (i_pHeap == NULL)
		i_pHeap = getDefaultHeap();*/

	assert(i_pHeap);

	return alloc(i_pHeap,i_size, DEFAULT_ALIGNMENT);
}

void operator delete(void * i_ptr, HeapManager * i_pHeap)
{
	assert(i_pHeap);
	if (i_ptr)
		free(heapManagerRef, i_ptr);
}

void * operator new[](size_t i_size)
{
	//DEBUG_PRINT("Calling new( size_t, HeapManager * ) with ( %Iu, %" PRIxPTR ").\n", i_size, i_pHeap);

	/*if (i_pHeap == NULL)
	i_pHeap = getDefaultHeap();*/

	//assert(i_pHeap);

	return alloc(heapManagerRef, i_size, DEFAULT_ALIGNMENT);
}

void operator delete[](void * i_ptr)
{
	if (i_ptr)
		free(heapManagerRef, i_ptr);
}

void * operator new(size_t i_size, NewAlignment i_align)
{	
	switch (i_align)
	{
	case NEW_ALIGN_16:
	case NEW_ALIGN_32:
		return alloc(heapManagerRef, i_size, i_align);
	default:
		return alloc(heapManagerRef, i_size, DEFAULT_ALIGNMENT);
	}
}

void operator delete(void * i_ptr, NewAlignment i_align)
{
	if (i_ptr)
		free(heapManagerRef, i_ptr);
}

void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line) {
	return alloc(heapManagerRef, i_size, DEFAULT_ALIGNMENT);
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line) {
	if (i_ptr)
		free(heapManagerRef, i_ptr);
}