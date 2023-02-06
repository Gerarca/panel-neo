//---------------------------------------------------------------------------
//
//	Component.hpp
//
//	Base class for all DSC_IComponent implmentations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Component.hpp"
#include "Debug.hpp"

//---------------------------------------------------------------------------

	CComponent::CComponent(VOID) : m_numRefCount(0)
	{
	}

//---------------------------------------------------------------------------

	CComponent::~CComponent(VOID)
	{
	}

//---------------------------------------------------------------------------

	CCriticalSection& CComponent::GetSyncLock(VOID)
	{
		return m_clsSyncLock;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CComponent::Query(IN char const* pszInterface, OUT VOID** ptrInterface)
	{
		//validate arguments
		if ((NULL == pszInterface) || (NULL == ptrInterface))
		{
			//validate arguments
			return IRESULT_E_BAD_ARGUMENTS;
		}

		//check for DSC_IComponent ID
		CLock lock = m_clsSyncLock;
		if (0 == strcmp(pszInterface, NAME_DSC_IComponent))
		{
			//increase ref count and return the pointer to this component
			DSC_IComponent* ptr = static_cast<DSC_IComponent*>(this);
			ptr->Acquire(NULL);

			//return the result
			*ptrInterface = ptr;
			return IRESULT_S_OK;
		}
		//unknown interface
		return IRESULT_E_NOT_IMPLEMENTED;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CComponent::Acquire(ICOUNT* ptrCount)
	{
		//increment the ref count within the critical section
		CLock lock = m_clsSyncLock;
#ifdef TRACK_COMPOMENT_LIFETIME
		DEBUG_PRINTF("[CComponent::Acquire] %p: %d\n", this, m_numRefCount + 1);
#endif
		//increment the ref count
		++m_numRefCount;
		if (NULL != ptrCount)
		{
			*ptrCount = m_numRefCount;
		}
		return IRESULT_S_OK;
	}

//---------------------------------------------------------------------------

	IRESULT ICALL CComponent::Release(ICOUNT* ptrCount)
	{
		//decrement the ref count within the critical section
		//and self-delete the component if the count drops to 0
		CLock lock = m_clsSyncLock;
		if (0 < m_numRefCount)
		{
			//decrement the ref count
			--m_numRefCount;
			if (NULL != ptrCount)
			{
				*ptrCount = m_numRefCount;
			}

			//did ref count drop to 0?
			if (0 == m_numRefCount)
			{
				//validate heap
				DEBUG_ASSERT(Platform::VALIDATE_HEAP_POINTER(this));

				//delete this object
#ifdef TRACK_COMPOMENT_LIFETIME
				DEBUG_PRINTF("[CComponent::Release] %p: %d\n", this, 0);
#endif
				delete this;
				return IRESULT_S_OK;
			}
		}

		//return the ref count
#ifdef TRACK_COMPOMENT_LIFETIME
		DEBUG_PRINTF("[CComponent::Release] %p: %d\n", this, m_numRefCount);
#endif
		return IRESULT_S_OK;
	}

//---------------------------------------------------------------------------
