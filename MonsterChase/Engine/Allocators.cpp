#include "HeapManager.h"

#include <assert.h>
#include <malloc.h>		// for _aligned_malloc
#include <inttypes.h>	// for print specifiers
#include <stdlib.h>		// for NULL

HeapManager * getDefaultHeap()
{
	static HeapManager * pDefaultHeap = nullptr;

	if (pDefaultHeap == nullptr)
	{
		static const size_t sizeDefaultHeap = 1024 * 1024;
		static const size_t alignDefaultHead = 4;

		void * pDefaultHeapMem = _aligned_malloc(sizeDefaultHeap, alignDefaultHead);
		assert(pDefaultHeapMem);

		static const unsigned int numDescriptors = 2048;

		pDefaultHeap = HeapManager::create(pDefaultHeapMem, sizeDefaultHeap, numDescriptors);
		if (pDefaultHeap == nullptr)
			_aligned_free(pDefaultHeapMem);
	}

	return pDefaultHeap;
}

// standard new & delete
void * operator new(size_t i_size)
{
	//DEBUG_PRINT("Calling new( size_t ) with ( %Iu ).\n", i_size);

	return _aligned_malloc(i_size, 4);
}

void operator delete(void * i_ptr)
{
	//DEBUG_PRINT("Calling delete( void * ) with ( %" PRIxPTR " ).\n", i_ptr);

	// don't delete NULL pointers. i guess we could also assert
	if (i_ptr)
		_aligned_free(i_ptr);
}

// array new[] and delete[]
void * operator new[](size_t i_size)
{
	//DEBUG_PRINT("Calling new[]( size_t ) with ( %Iu ).\n", i_size);

	void * ptr = _aligned_malloc(i_size, 4);
	//DEBUG_PRINT("new[]( size_t ) returning %" PRIxPTR ".\n", ptr);
	return ptr;
}

void operator delete[](void * i_ptr)
{
	//DEBUG_PRINT("Calling delete[]( void * ) on %" PRIxPTR ".\n", i_ptr);

	// don't delete NULL pointers. i guess we could also assert
	if (i_ptr)
		_aligned_free(i_ptr);
}

enum NewAlignment
{
	NEW_ALIGN_DEFAULT,
	NEW_ALIGN_16 = 16,
	NEW_ALIGN_32 = 32
};

void * operator new(size_t i_size, NewAlignment i_align)
{
	//DEBUG_PRINT("Calling new( size_t, NewAlignment ) with ( %Iu, %d ).\n", i_size, i_align);

	switch (i_align)
	{
	case NEW_ALIGN_16:
	case NEW_ALIGN_32:
		return _aligned_malloc(i_size, i_align);
	default:
		return _aligned_malloc(i_size, 4);
	}
}

// needed to keep compiler happy if above operator throws which
// is important if exception handling is enabled
void operator delete(void * i_ptr, NewAlignment i_align)
{
	//DEBUG_PRINT("Calling delete( void *, NewAlignment ) with ( %" PRIxPTR ", %d ).\n", i_ptr, i_align);
	//DEBUG_PRINT("BTW... this should never happen.\n");

	// don't attempt to delete NULL pointers. i guess we could also assert
	if (i_ptr != 0)
		_aligned_free(i_ptr);
}


// tracking allocators
void * operator new(size_t i_size, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling new( size_t ) with ( %Iu ) from %s:%d.\n", i_size, i_pFile, i_Line);

	void * pMem = _aligned_malloc(i_size, 4);

	// StoreTrackingInfo( pMem, i_pFile, i_Line);

	return pMem;
}

void operator delete(void * i_ptr, const char * i_pFile, unsigned int i_Line)
{
	//DEBUG_PRINT("Calling delete( void *, unsigned int, const char * ) with ( %" PRIxPTR ", %s, %d ).\n", i_ptr, i_pFile, i_Line);
	//DEBUG_PRINT("BTW... this should never happen.\n");

	// don't attempt to delete NULL pointers. i guess we could also assert
	if (i_ptr != 0)
	{
		// ReleaseTrackingInfo( i_ptr );
		_aligned_free(i_ptr);
	}
}

void * operator new(size_t i_size, HeapManager * i_pHeap)
{
	//DEBUG_PRINT("Calling new( size_t, HeapManager * ) with ( %Iu, %" PRIxPTR ").\n", i_size, i_pHeap);

	if (i_pHeap == NULL)
		i_pHeap = getDefaultHeap();

	assert(i_pHeap);

	static const unsigned int defaultAlignment = 4;

	return i_pHeap->_alloc(i_size, defaultAlignment);
}

void operator delete(void * i_ptr, HeapManager * i_pHeap, unsigned int i_align)
{
	//DEBUG_PRINT("Calling delete( void *, HeapManager *, unsigned int  ) with ( %" PRIxPTR ", %" PRIxPTR ", %d ).\n", i_ptr, i_pHeap, i_align);
	//DEBUG_PRINT("BTW... this should never happen.\n");

	// don't attempt to delete NULL pointers. i guess we could also assert
	if (i_ptr != nullptr)
	{
		if (i_pHeap == NULL)
			i_pHeap = getDefaultHeap();

		assert(i_pHeap);

		i_pHeap->_free(i_ptr);
	}
}

void * operator new(size_t i_size, HeapManager * i_pHeap, unsigned int i_align)
{
	//DEBUG_PRINT("Calling new( size_t, HeapManager *, unsigned int ) with ( %Iu, %" PRIxPTR ", %d).\n", i_size, i_pHeap, i_align);

	if (i_pHeap == NULL)
		i_pHeap = getDefaultHeap();

	assert(i_pHeap);

	return i_pHeap->_alloc(i_size, i_align);

}

void operator delete(void * i_ptr, HeapManager * i_pHeap)
{
	//DEBUG_PRINT("Calling delete( void *, HeapManager * ) with ( %" PRIxPTR ", %" PRIxPTR " ).\n", i_ptr, i_pHeap);

	// don't attempt to delete NULL pointers. i guess we could also assert
	if (i_ptr != 0)
	{
		if (i_pHeap == nullptr)
			i_pHeap = getDefaultHeap();

		assert(i_pHeap);

		i_pHeap->_free(i_ptr);
	}
}
