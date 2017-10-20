#pragma once
#include <stdint.h>
#include "String_Functions.h"
class StringPool
{
public:
	StringPool * Create(size_t i_bytesInPool);
	~StringPool();

	// find string in pool - adding it if it's not there
	const char * add(const char * i_pString);
	// find string in pool - don't add if it's not there
	const char * find(const char * i_pString);
private:
	StringPool(uint8_t * i_pPool, size_t i_sizePool);
	uint8_t *m_pStartBuffer;
	uint8_t *m_pEndBuffer;
	uint8_t *m_pEndStrings;
};


namespace StringPoolProxy {
	static StringPool *stringPoolRef;
	StringPool * GetStringPool();
	void SetStringPool(StringPool *pool);
}