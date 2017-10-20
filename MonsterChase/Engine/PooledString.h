#pragma once
#include "StringPool.h"
#include <string>

using namespace StringPoolProxy;

class PooledString
{
public:

	explicit PooledString(const char * i_pString) :
		m_pString(GetStringPool()->add(i_pString))
	{ }

	PooledString(const PooledString & i_other) :
		m_pString(i_other.m_pString)
	{ }

	PooledString & operator =(const PooledString &i_other) {
		m_pString = i_other.m_pString;
	}

	bool operator ==(const PooledString & i_other) {
		return m_pString == i_other.m_pString;
	}

	operator bool() const {
		return m_pString != nullptr;
	}

	char * duplicate() const {
		return m_pString ? _strdup(m_pString) : nullptr;
	}

	const char * get() const {
		return m_pString;
	}

private:
	const char *m_pString;
};

