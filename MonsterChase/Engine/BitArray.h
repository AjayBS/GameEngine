#pragma once
#include "HeapManager.h"
#include <stdio.h>
#include <string.h>
#include <math.h>  
#ifdef _WIN64
typedef uint64_t type_t;
#define bitShiftValue 1i64
#else
typedef uint32_t type_t;
#define bitShiftValue 1
#endif


class HeapManager;

class BitArray
{
public:
	BitArray();
	BitArray(const size_t i_numBits, BitArray *i_pManager, bool i_startClear = true);
	~BitArray();

	BitArray * Create(size_t i_numBytes, BitArray *i_pManager, bool i_startClear = true);
	void ClearAll(void);
	void SetAll();

	bool AreAllClear(void) const;
	bool AreAllSet(void) const;

	bool IsBitSet(const size_t i_bitNumber) const;
	bool IsBitClear(const size_t i_bitNumber) const;

	void SetBit(const size_t i_bitNumber);
	void ClearBit(const size_t i_bitNumber);

	size_t GetFirstClearBit() const;
	size_t GetFirstSetBit() const;

	//bool operator[](size_t i_index) const;

	size_t GetNumberOfBits();
	size_t GetBitValue() const;

private:
	// TO_DO change this to be compatible to both 32 and 64 bit.
	type_t *m_pBits;
	 const static size_t bitsPerBytes = 8;
	// size_t m_numBytes;
	 size_t m_numBits;
};

