/*
 * Søren Gullach 9/12/23 
 * 
 * Controls the interlock semafores for sharing data between CM7 and CM4
 * 
 **/

#include "SharedDataCtrl.h"


CSharedDataControl *pCSharedDataControl[HSEM_SEMID_MAX + 1] = { 0 };

#ifdef CORE_CM7
extern "C" void HSEM1_IRQHandler()
{
	// Disable Interrupts
	HSEM->C1IER &= ~(HSEM->C1MISR);
	
	uint32_t SemMask = HSEM->C1MISR; // Use interrupt line 1 for CPU1 Master
	for (size_t i = 0; i < HSEM_SEMID_MAX + 1; i++, SemMask >>= 1)
	{
		if (pCSharedDataControl[i] != 0 && (SemMask & 0x01))
			pCSharedDataControl[i]->FreeNotified();
	}			
	// Clear Flags
	HSEM->C1ICR = HSEM->C1MISR;
}
#endif
#ifdef CORE_CM4
extern "C" void HSEM2_IRQHandler()
{
	// Disable Interrupts
	HSEM->C2IER &= ~(HSEM->C2MISR);
	
	uint32_t SemMask = HSEM->C2MISR; // Use interrupt line 2 for CPU2 Master
	for (size_t i = 0; i < HSEM_SEMID_MAX + 1; i++, SemMask >>= 1)
	{
		if (pCSharedDataControl[i] != 0 && (SemMask & 0x01))
			pCSharedDataControl[i]->FreeNotified();
	}			
	// Clear Flags
	HSEM->C2ICR = HSEM->C2MISR;
}
#endif


