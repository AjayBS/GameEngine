#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "EngineTypes.h"
#include "Debug.h"
#include "Macros.h"

class HeapManager;

struct BlockDescriptor
{
	void *m_pMemoryPointer;
	size_t m_sizeBlock;
	BlockDescriptor *m_pNext;
	BlockDescriptor *m_pPrevious;
};

class HeapManager
{

public:
	void* pFreeMemoryList;
	size_t heapSize;
	myint_t numDescriptors;
	size_t allocatedCount;
	size_t descriptorStorage;	
	HeapManager();
	~HeapManager();
	/*void* alloc(size_t i_size, const myint_t alignment);*/
	/*void free(void* deallocation_pointer);*/
	//void CreateHeapManager(void *pHeapMemory, const size_t sizeHeap, const myint_t numDescriptors);
	/*void AddFreedBlockToTheFreeDescriptorList(BlockDescriptor* freedBlock);*/
	//size_t GetAvailableSize();
	//myint_t ShowFreeBlocks();
	//myint_t ShowAllocatedBlocks();
	//myint_t GetNumberOfDescriptors();
	//void GarbageCollect();
	///*void ResetFreeDescriptor();*/
	//void Combine(BlockDescriptor *presentBlock, BlockDescriptor *previousBlock);
	inline size_t GetAvailableSize(const HeapManager * i_pManager) const{

		BlockDescriptor *tempFreeDescriptorList = i_pManager->pOutstandingAllocationList;
		//size_t requiredStorage = GetNumberOfDescriptors() * sizeof(BlockDescriptor);

		size_t occupiedSize = 0;

		while (tempFreeDescriptorList != nullptr) {
			occupiedSize += tempFreeDescriptorList->m_sizeBlock;
			tempFreeDescriptorList = tempFreeDescriptorList->m_pPrevious;
		}

		return (i_pManager->heapSize - i_pManager->descriptorStorage - occupiedSize);

	}

	inline myint_t GetNumberOfDescriptors() const
	{
		BlockDescriptor *tempFreeDescriptorList = pFreeDescriptorList;
		myint_t numOfDescriptors = 0;
		while (tempFreeDescriptorList != nullptr)
		{
			tempFreeDescriptorList = tempFreeDescriptorList->m_pPrevious;
			numOfDescriptors++;
		}
		return numOfDescriptors;
	}

	inline myint_t ShowFreeBlocks() const{

		myint_t availableDescriptors = GetNumberOfDescriptors();
		return availableDescriptors;
		//printf_s("%d", availableDescriptors);
	}

	inline myint_t ShowAllocatedBlocks() const{
		BlockDescriptor *tempAllocator = pOutstandingAllocationList;
		myint_t allocatedListCount = 0;

		do {
			if (tempAllocator == nullptr) {
				break;
			}
			allocatedListCount++;
			tempAllocator = tempAllocator->m_pPrevious;
		} while (tempAllocator != nullptr);
		return allocatedListCount;
		//printf_s("%d", availableDescriptors);
	}
	BlockDescriptor *pOutstandingAllocationList;
	BlockDescriptor *pFreeDescriptorList;
};

namespace HeapManagerProxy
{
	static HeapManager *heapManagerRef;

	HeapManager* CreateHeapManager(void *pHeapMemory, size_t sizeHeap, const myint_t numDescriptors);
	void* alloc(HeapManager * i_pManager, size_t i_size, const myint_t alignment);
	void free(HeapManager * i_pManager, void* deallocation_pointer);
	void AddFreedBlockToTheFreeDescriptorList(HeapManager * i_pManager, BlockDescriptor* freedBlock);
	void ResetFreeDescriptor(HeapManager * i_pManager);
	
	void GarbageCollect(HeapManager * i_pManager);
	void Combine(BlockDescriptor *presentBlock, BlockDescriptor *previousBlock);
	HeapManager * GetHeapManager();
	void SetHeapManager(HeapManager *heap);
	
	

}

enum NewAlignment
{
	NEW_ALIGN_DEFAULT,
	NEW_ALIGN_16 = 16,
	NEW_ALIGN_32 = 32
};

//standard new / delete
void * operator new(size_t i_size);
void operator delete(void * i_ptr);

void * operator new(size_t i_size, HeapManager * i_pHeap);
void operator delete(void * i_ptr, HeapManager * i_pHeap);

void * operator new[](size_t i_size);
void operator delete[](void * i_ptr);

void * operator new(size_t i_size, NewAlignment i_align);
void operator delete(void * i_ptr, NewAlignment i_align);

// tracking allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line);
void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line);





