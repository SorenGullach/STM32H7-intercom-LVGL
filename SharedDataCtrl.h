/*
 * Søren Gullach 9/12/23 
 * 
 * Controls the interlock semafores for sharing data between CM7 and CM4
 * 
 **/

#pragma once

#include <stm32h7xx.h>
#include "stdint.h"
#include <assert.h>

#define SRAM4_Start 0x38000000
#define SRAM4_End 0x3800FFFF

struct _SharedDataMapBase
{
	virtual uint8_t HSEM_ID() = 0; 
};
template<int ID>
struct _SharedDataMap : public _SharedDataMapBase
{
	static_assert(ID <= HSEM_SEMID_MAX);
	
	const uint8_t _HSEM_ID = ID; // shared semafor
	virtual uint8_t HSEM_ID() override
	{
		return _HSEM_ID;
	}
 
};

class CSharedDataControl;
extern CSharedDataControl *pCSharedDataControl[HSEM_SEMID_MAX + 1];
class CSharedDataControl
{
private:
	bool HSEM_Take1(uint8_t SemID)
	{
		assert(SemID <= HSEM_SEMID_MAX);
#ifdef CORE_CM7
		return HSEM->RLR[SemID] == ((HSEM_CPU1_COREID << HSEM_RLR_COREID_Pos) | HSEM_RLR_LOCK);
#endif
#ifdef CORE_CM4
		return HSEM->RLR[SemID] == ((HSEM_CPU2_COREID << HSEM_RLR_COREID_Pos) | HSEM_RLR_LOCK);
#endif
	}
	void HSEM_Release(uint8_t SemID)
	{
		assert(SemID <= HSEM_SEMID_MAX);
#ifdef CORE_CM7
		HSEM->R[SemID] = (HSEM_CPU1_COREID << HSEM_RLR_COREID_Pos);
#endif
#ifdef CORE_CM4
		HSEM->R[SemID] = (HSEM_CPU2_COREID << HSEM_RLR_COREID_Pos);
#endif
	}
	
public:
	CSharedDataControl()
	{
#ifdef CORE_CM7
		NVIC_EnableIRQ(HSEM1_IRQn); // we use interrupt line HEMS1, from CM4 to CM7
#endif
#ifdef CORE_CM4
		NVIC_EnableIRQ(HSEM2_IRQn); // we use interrupt line HEMS2, from CM7 to CM4
#endif
	}
	
	void Register(_SharedDataMapBase * const data)
	{
		// TODO extend to allow serveal objects to register on the same HSEM
		pCSharedDataControl[data->HSEM_ID()] = this; // fore the interrupt handler to find object
	}

	/*
	 * call this to lock data for modify and signal to other CPU
	 * */
	bool GetAccessModify(_SharedDataMapBase * const data)
	{
		return HSEM_Take1(data->HSEM_ID());
	}
	/*
	 * call this for lock data for read and no signal
	 * */
	bool GetAccessRead(_SharedDataMapBase * const data)
	{
		return HSEM_Take1(data->HSEM_ID());
	}

	/*
	 * Release locked data and signal to other CPU
	 * */
	void ReleaseAccessModify(_SharedDataMapBase * const data)
	{
		// enable interrupt for the receiver
#ifdef CORE_CM7
		HSEM->C2IER |= (1 << data->HSEM_ID()); // enable interrupt on CM4
#endif
#ifdef CORE_CM4
		HSEM->C1IER |= (1 << data->HSEM_ID()); // enable interrupt on CM7
#endif
		HSEM_Release(data->HSEM_ID());
		
	}
	/*
	 * Release locked data and no signal to other CPU
	 * */
	void ReleaseAccessRead(_SharedDataMapBase * const data)
	{
		HSEM_Release(data->HSEM_ID());
	}

	virtual void FreeNotified() {};
};

/*****************************************************************
 * Allocation of mem in SRAM4
 * */
class CPoolSRAM4 {
public:
	void* alloc(size_t nbytes)
	{
		void * mem = pPoolSRAM4;
		pPoolSRAM4 = (void*)((int)pPoolSRAM4 + nbytes + nbytes % 4);
		assert((int)pPoolSRAM4 < SRAM4_End);
		return mem;
	}
	void dealloc(void* p)
	{
		// nothing to dealocate in SRAM4
	}
private:
	void *pPoolSRAM4 = (void *)SRAM4_Start; // current free pos in SRAM4
};

inline void * operator new(size_t nbytes, CPoolSRAM4& pool)
{
	return pool.alloc(nbytes);
}