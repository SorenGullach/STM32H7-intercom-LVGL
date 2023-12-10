/*
 * Søren Gullach 9/12/23 
 * 
 * Shared data between CM7 and CM4
 * 
 **/

#include "SharedData.h"
#include "SharedDataCtrl.h"

CPoolSRAM4 PoolSRAM4; // Create pool object

// Create the shared objects
struct _ToCM7 * const pToCM7 = new(PoolSRAM4) _ToCM7();
struct _ToCM7_1 * const pToCM7_1 = new(PoolSRAM4) _ToCM7_1();
struct _ToCM4 * const pToCM4 = new(PoolSRAM4) _ToCM4();
