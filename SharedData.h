/*
 * Søren Gullach 9/12/23 
 * 
 * Shared data between CM7 and CM4
 * 
 **/

#pragma once

#include "SharedDataCtrl.h"
#include "stdint.h"

// Data to CM7 from CM4
struct _ToCM7 : public _SharedDataMap<1>
{
	uint32_t M4CounterFree;
	uint32_t Data1, Data2, Data3; // etc
}__ALIGNED(4);

// Data to CM7 from CM4
struct _ToCM7_1 : public _SharedDataMap<2>
{
	uint32_t M4Counter;
	uint32_t Data1, Data2, Data3; // etc
}__ALIGNED(4);

// Data to CM4 from CM7
struct _ToCM4 : public _SharedDataMap<3>
{
	uint32_t M7Counter;
	uint32_t Data1, Data2, Data3; // etc
}__ALIGNED(4);
 
extern struct _ToCM7 * const pToCM7;
extern struct _ToCM7_1 * const pToCM7_1;
extern struct _ToCM4 * const pToCM4;

