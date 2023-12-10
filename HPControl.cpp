
#include "HPControl.h"
#include "SharedData.h"

HPControl Control;

//////////////////////////////////////////////////////////////////////////
// Called from main
extern "C" void InitControl()
{
	Control.Init();
}

// Called from main, to get things done
extern "C" uint32_t TickTack()
{
	Control.TickTack();
	return 10;
}
/////////////////////////////////////////////////////////////////////////

void HPControl::Init()
{
	Register(pToCM4);
	CanBus.Init();
}

void HPControl::TickTack()
{
//	CanBus.TickTack();
	if (GetAccessModify(pToCM7)) // send somthing to CM7, get modify access
	{
		pToCM7->M4CounterFree++;
		ReleaseAccessModify(pToCM7); // Notify that data have changed
	}
}

void HPControl::FreeNotified() // virtual function, called on changed from the CM7
{
	if (GetAccessRead(pToCM4)) // get read access
	{
		uint32_t c = pToCM4->M7Counter; // read data
		ReleaseAccessRead(pToCM4);
		if (GetAccessModify(pToCM7_1)) // send something back to CM7
		{
			pToCM7_1->M4Counter = c;
			ReleaseAccessModify(pToCM7_1); // Notify that data have changed
		}
	}
}

