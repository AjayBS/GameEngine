#pragma once
inline myint_t HeapManager::ShowFreeBlocks() const{
	myint_t availableDescriptors = numDescriptors - ShowAllocatedBlocks();
	return availableDescriptors;
	//printf_s("%d", availableDescriptors);
}

inline myint_t HeapManager::ShowAllocatedBlocks() const{
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

inline size_t HeapManager::GetAvailableSize() const{

	BlockDescriptor *tempFreeDescriptorList = pFreeDescriptorList;

	size_t availableSize = 0;

	do {

		availableSize += tempFreeDescriptorList->m_sizeBlock;

		tempFreeDescriptorList = tempFreeDescriptorList->m_pPrevious;

	} while (tempFreeDescriptorList->m_pPrevious != nullptr);

	return availableSize;

}