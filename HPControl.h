#pragma once

#include "SharedDataCtrl.h"
#include "SharedData.h"
#include <CCANBus.h>

class HPControl : CSharedDataControl
{
public:
	HPControl()
		: CSharedDataControl()
	{
	}
	
	void Init();
	
	void TickTack();
	
	virtual void FreeNotified() override;
	
	CCanBus CanBus;
};