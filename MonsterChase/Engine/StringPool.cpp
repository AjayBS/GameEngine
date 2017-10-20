#include "StringPool.h"
#include "HeapManager.h"
#include <string>

using namespace StringPoolProxy;
using namespace String_FunctionsProxy;

StringPool::StringPool(uint8_t * i_pPool, size_t i_sizePool)
{
	m_pStartBuffer = reinterpret_cast<uint8_t *>(i_pPool);
	m_pEndBuffer = reinterpret_cast<uint8_t *>(i_pPool) + i_sizePool;
	m_pEndStrings = m_pStartBuffer;
}


StringPool * StringPool::Create(size_t i_bytesInPool)
{
	uint8_t * pool = new uint8_t[i_bytesInPool];
	StringPoolProxy::stringPoolRef = new StringPool(pool, i_bytesInPool);
	//StringPoolProxy::SetStringPool();
	return stringPoolRef;
}

StringPool::~StringPool()
{
}

const char * StringPool::add(const char * i_pString)
{
	size_t val = strlen(i_pString);
	int size = (val <= INT_MAX) ? (int)((size_t)val) : -1;
	if (find(i_pString) == nullptr) {
		char *snum = new char[sizeof(int)];
		_itoa_s(size, snum, 10, 2);
		String_FunctionsProxy::str_cpy(reinterpret_cast<char *>(m_pEndStrings), snum);
		m_pEndStrings = m_pEndStrings + sizeof(int);
		String_FunctionsProxy::str_cpy(reinterpret_cast<char *>(m_pEndStrings), i_pString);
		m_pEndStrings += size;
		return reinterpret_cast<char *>(m_pEndStrings) - size;
	}
	else {
		return find(i_pString);
	}

}

const char * StringPool::find(const char * i_pString)
{
	uint8_t *tempPointer = m_pStartBuffer;
	while (tempPointer != m_pEndStrings)
	{
		int size = static_cast<int>(*tempPointer);
		tempPointer += sizeof(int);
		if (strcmp(reinterpret_cast<char *>(tempPointer), i_pString)) {
			return i_pString;
		}
		tempPointer += size;
	}
	//tempPointer += sizeof(int);
	return nullptr;
}

StringPool * StringPoolProxy::GetStringPool()
{
	return stringPoolRef;
}

void StringPoolProxy::SetStringPool(StringPool * pool)
{
	stringPoolRef = pool;
}
