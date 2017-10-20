#include "StrongPointer.h"

//template<typename T>
//inline void StrongPointer<T>::ReleaseCurrentReference()
//{
//	if (--(*m_pCounters.refCount) == 0)
//	{
//		delete m_pCounters;
//		delete m_pObject;
//	}
//	m_pObject = nullptr;
//	m_pCounters = nullptr;
//}
//
//template<typename T>
//inline void StrongPointer<T>::AcquireNewReference(const StrongPointer & i_other)
//{
//	m_pObject = i_other.m_pObject;
//	m_pCounters.refCount = i_other.m_pCounters.refCount++;
//	m_pCounters.weakCount = i_other.m_pCounters.weakCount;
//	//m_pRefCount();
//}
//
//
////template<class T>
////SmartPtr<T>::AcquireNewReference(const SmartPtr & i_other)
////{
////
////}
