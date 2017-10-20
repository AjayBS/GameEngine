#pragma once
#include"StrongPointer.h"

template<typename T>
class WeakPointer
{
private:
	Counters *m_pCounters;
	T *m_pObject;
public:
	inline StrongPointer<T> WeakPointer<T>::Acquire()
	{
		if (m_pCounters->strongCount > 0)
			return StrongPointer<Actor>(m_pObject, m_pCounters);
		else
		return StrongPointer<Actor>(nullptr);
	}

	
	inline void WeakPointer<T>::DecrementWeakReference()
	{
		(m_pCounters->weakCount)--;
	}

	WeakPointer() {

	}

	WeakPointer(T * i_ptr) {
		i_ptr = NULL;
	}
	
	WeakPointer(const StrongPointer<T> & i_other) :
		m_pObject(i_other.GetObjectReference()),    // Copy the pointer to the tracked object
		m_pCounters(i_other.GetCounter()) // Copy the pointer to the master ref count
	{
		// We've created a new smart pointer
		// Increment the master reference count
		(i_other.GetCounter()->weakCount)++;

	}

	~WeakPointer()
	{
		DecrementWeakReference();
	}

	WeakPointer<T> &operator=(const WeakPointer<T> & i_other)
	{
		if (&i_other == this)
			return *this;
		if (&i_other == nullptr) {
			DecrementWeakReference();
		}
		(this->m_pCounters->weakCount)++;
		return *this;
	}

	WeakPointer<T> &operator=(const StrongPointer<T> & i_other)
	{
		if (&i_other == nullptr) {
			return *this;
		}
		else {
			m_pCounters = i_other.GetCounter();
			m_pObject = i_other.GetObjectReference();
			m_pCounters->weakCount++;
		}
		return *this;
	}

	WeakPointer<T> & operator=(const nullptr_t)
	{
		DecrementWeakReference();
		return *this;
	}


	bool operator==(const WeakPointer<T> & i_other) const
	{
		if (this == &i_other)
			return true;
		else
			return false;
	}

	bool operator==(const std::nullptr_t) const
	{
		if (this == nullptr)
			return true;
		else
			return false;
	}

	

};


