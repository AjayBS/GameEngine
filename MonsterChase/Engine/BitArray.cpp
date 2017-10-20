#include "BitArray.h"
#include <intrin.h>  


BitArray::BitArray()
{
}

BitArray::BitArray(const size_t i_numBits, BitArray * i_pManager, bool i_startClear)
{
	Create(i_numBits, i_pManager,i_startClear);
}


BitArray::~BitArray()
{
}

BitArray * BitArray::Create(size_t i_numBits, BitArray * i_pManager, bool i_startClear)
{	
	m_pBits = reinterpret_cast<type_t *>(i_pManager) + sizeof(BitArray);    //new uint8_t[i_numBits / bitsPerBytes];
	assert(m_pBits == nullptr ? true:false);
	//m_numBytes = i_numBits / bitsPerBytes;
	//printf_s("%d",(i_numBits % bitsPerBytes));
	i_numBits = i_numBits + (GetBitValue() - (i_numBits % GetBitValue()));
	m_numBits = i_numBits;
	memset(m_pBits, i_startClear ? ~0 : 0, i_numBits / bitsPerBytes);

	return (BitArray *)m_pBits;
}

void BitArray::ClearAll(void)
{
	memset(m_pBits, 0, m_numBits / bitsPerBytes);
}

void BitArray::SetAll()
{
	memset(m_pBits, ~0, m_numBits / bitsPerBytes);
}

bool BitArray::AreAllClear(void) const
{
	unsigned int index = 0;
	size_t m_numBytes = m_numBits / bitsPerBytes;
	while ((m_pBits[index] == 0x00) && (index < m_numBytes)) {
		index++;
	}

	if (index == m_numBytes) {
		return true;
	}

	return false;
}

bool BitArray::AreAllSet(void) const
{
	return !AreAllClear();
}

bool BitArray::IsBitSet(const size_t i_bitNumber) const
{
	size_t byteNumber = static_cast<size_t>(floor((float)i_bitNumber / GetBitValue()));
	if (m_pBits[byteNumber] & bitShiftValue << (i_bitNumber - (byteNumber * GetBitValue()))) {
		return true;
	}
	return false;
}

bool BitArray::IsBitClear(const size_t i_bitNumber) const
{
	return !IsBitSet(i_bitNumber);
}

void BitArray::SetBit(const size_t i_bitNumber)
{
	size_t byteNumber = static_cast<size_t>(floor((float)i_bitNumber / GetBitValue()));
	m_pBits[byteNumber] |= bitShiftValue << (i_bitNumber - (byteNumber * GetBitValue()));
}

void BitArray::ClearBit(const size_t i_bitNumber)
{
	size_t byteNumber = static_cast<size_t>(floor((float)i_bitNumber / GetBitValue()));
	m_pBits[byteNumber] &= ~(bitShiftValue << (i_bitNumber - (byteNumber * GetBitValue())));
}

size_t BitArray::GetFirstSetBit() const
{
	size_t index = 0;
	size_t m_numBytes = m_numBits / bitsPerBytes;
	// quick skip bytes where no bits are set   
	while ((m_pBits[index] == 0x00) && (index < m_numBytes)) {
		index++;
	}
    // Check if it has reached the end
	if ((index*GetBitValue()) == m_numBits) {
		return GARBAGE_RETURN_VALUE_OF_BIT;
	}
	else {
		type_t byte = m_pBits[index];
		unsigned long bit;
		size_t bitset;
#if _WIN64
		unsigned char isNonzero = _BitScanForward64(&bit, byte);
#else
		unsigned char isNonzero = _BitScanForward(&bit, byte);
#endif // WIN
		if (isNonzero)
		{
			bitset = index * GetBitValue() + bit;
		}
		else {
			return GARBAGE_RETURN_VALUE_OF_BIT;
		}
		return bitset;
	}
}

size_t BitArray::GetNumberOfBits()
{
	return m_numBits;
}

size_t BitArray::GetBitValue() const
{
#if _WIN64
	return 64;
#else
	return 32;
#endif
}

size_t BitArray::GetFirstClearBit() const
{
	size_t index = 0;
	size_t m_numBytes = m_numBits / bitsPerBytes;
	// quick skip bytes where no bits are set   
	while ((m_pBits[index] == 0xffffffffffffffff) && (index < m_numBytes)) {
		index++;
	}

	if ((index*GetBitValue()) == m_numBits) {
		return GARBAGE_RETURN_VALUE_OF_BIT;
	}
	else {

		type_t byte = m_pBits[index];
		unsigned long bit;
		
		size_t bitset;
#if _WIN64
		type_t mask = UINT64_MAX;
		unsigned char isNonzero = _BitScanForward64(&bit, byte ^ mask);
#else
		type_t mask = UINT32_MAX;
		unsigned char isNonzero = _BitScanForward(&bit, byte ^ mask);
#endif // WIN


		if (isNonzero)
		{
			bitset = index * GetBitValue() + bit;
		}
		else {
			return GARBAGE_RETURN_VALUE_OF_BIT;
		}
		// now we've found the byte and the bit
		return bitset;
	}
}