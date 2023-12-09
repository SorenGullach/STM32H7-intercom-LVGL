
#include "HPControl.h"
#include "SharedData.h"

HPControl Control;

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

void HPControl::Init()
{
	CanBus.Init();
}

void HPControl::TickTack()
{
	CanBus.TickTack();
	if (GetAccessModify())
	{
		pSharedTest->M4CounterFree++;
		ReleaseAccessModify();
	}
}

void HPControl::FreeNotified()
{
	if (GetAccessRead())
	{
		uint32_t c = pSharedTest->M7Counter;
		ReleaseAccessRead();
		if (GetAccessModify())
		{
			pSharedTest->M4Counter = c;
			ReleaseAccessModify();
		}
	}
}

