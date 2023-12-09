#pragma once

#include "SharedDataCtrl.h"
#include "SharedData.h"
#include <CCANBus.h>

class HPControl : CSharedDataControl
{
public:
	HPControl()
		: CSharedDataControl(HSEM_ID_T_CM7, HSEM_ID_T_CM4)
	{
		
	}
	void Init();
	
	void TickTack();
	
	virtual void FreeNotified() override;
	
	CCanBus CanBus;
};