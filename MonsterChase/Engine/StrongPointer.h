#pragma once
#include "GameObject.h"

struct Counters {
	long strongCount;
	long weakCount;
};

template<typename T>
class StrongPointer {
public:
	
	StrongPointer(T *i_ptr) :
		m_pObject(i_ptr),
		m_pCounters(new Counters)
			{
		m_pCounters->strongCount= 1;
		m_pCounters->weakCount = 0;
			}
	
	StrongPointer(const StrongPointer &i_other) :
				m_pObject(i_other.m_pObject)  ,  // Copy the pointer to the tracked object
				m_pCounters(i_other.m_pCounters) // Copy the pointer to the master ref count
			{
				// We've created a new smart pointer
				// Increment the master reference count
				(m_pCounters->strongCount)++;
		
			}

	T* GetObjectReference() const {
		return m_pObject;
	}

	Counters* GetCounter() const {
		return m_pCounters;
	}

	~StrongPointer()
			{
				ReleaseCurrentReference();
			}
	T * operator->()
			{
				return m_pObject;
			}
			// indirection operator
			T & operator*()
			{
				//assert(m_ptr != nullptr);
		
				return *m_pObject;
			}
	
	StrongPointer<T> & operator=(const StrongPointer<T> & i_other)
			{
				if (&i_other == this)
					return *this;
		
				ReleaseCurrentReference();
		
				if (&i_other == nullptr) {
					m_pCounters = nullptr;
					m_pObject = nullptr;
				}
				else {
					AcquireNewReference(i_other);
				}		
		
				return *this;
			}

	StrongPointer<T> & operator=(const nullptr_t)
	{
		ReleaseCurrentReference();
		return *this;
	}

	bool operator==(const StrongPointer<T> & i_other) const
	{
		if (this == &i_other)
			return false;
		else
			return true;
	}

	bool operator==(const nullptr_t) const
	{
		if (this == nullptr)
			return true;
		else
			return false;
	}

	StrongPointer(T *i_ptr, Counters *i_pCounters) :
		m_pObject(i_ptr),
		m_pCounters(i_pCounters)
	{
		//m_pCounters->refCount = 1;
		//m_pCounters->weakCount = 0;
		(m_pCounters->strongCount)++;
	}
	

	inline void ReleaseCurrentReference() {
		if (--(m_pCounters->strongCount) == 0)
		{
			//delete m_pCounters;
			delete m_pObject;
		}
		m_pObject = nullptr;
		m_pCounters = nullptr;
	}

	inline void AcquireNewReference(const StrongPointer & i_other) {
		m_pObject = i_other.m_pObject;
		m_pCounters->strongCount = i_other.m_pCounters->strongCount++;
		m_pCounters->weakCount = i_other.m_pCounters->weakCount;
		//m_pRefCount();
	}

private:
	T *m_pObject;
	Counters *m_pCounters;
};