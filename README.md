# STM32H7-intercom-LVGL
Based on the Riverdi RVT70HSSNWC00-B.

This is my take on how to implement a shared data between the CM7 and CM4 core on the STM32H7.

The test code is based on the Riverdi STM32CubeMX example (https://controllerstech.com/lvgl-on-riverdi-stm32-h7-display/#google_vignette), and imported into two VisualGDB projects. Maybe in the future I can upload an example of how to avoid the STM32CubeIde :-)

The shared data is placed in D3 domain at address SRAM4.
The goal was to make a mempool at SRAM4 that can be allocated in blocks, each have a HSEM to do the blocking and signal that changes have been made.

+ SharedData.h/cpp holds the structs that is shared.
+ SharedDataCtrl.h/cpp do the actual control of the interchange.
+ HPControl.h/cpp is an example of how to use the CSharedDataControl class.

An exampe of a shared object, notice the inherited _SharedDataMap<1>, 1 being the HSEM that controls this block of mem.
```
// Data to CM7 from CM4
struct _ToCM7 : public _SharedDataMap<1>
{
	uint32_t M4CounterFree;
	uint32_t Data1, Data2, Data3; // etc
}__ALIGNED(4);
```
To create the shared object, use "new" with the PoolSRAM4 mempool mannager
````
// Create the shared objects
struct _ToCM7 * const pToCM7 = new(PoolSRAM4) _ToCM7();
struct _ToCM7_1 * const pToCM7_1 = new(PoolSRAM4) _ToCM7_1();
struct _ToCM4 * const pToCM4 = new(PoolSRAM4) _ToCM4();
````
HPControl shows how to use the shared mem object, this code is from the CM4 side, the CM7 side is equal, except flow is reversed.
```
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
```
Remember to call some sort of "Init" of the (HPControl) class, this must be done after the static SharedData is allocated. i.e. From main()
The Register function sets up the pointers for the HSEM interrupt to work. (the HSEM interrupt is diverted to the correct FreeNotified function)
```
Register(pToCM4);
```

Papers to read: 
+ RM0399 https://www.st.com/resource/en/reference_manual/dm00176879-stm32h745755-and-stm32h747757-advanced-armbased-32bit-mcus-stmicroelectronics.pdf 
+ RM0433 https://www.st.com/resource/en/reference_manual/dm00314099-stm32h742-stm32h743-753-and-stm32h750-value-line-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf 
+ AN5617 https://www.st.com/resource/en/application_note/an5617-stm32h745755-and-stm32h747757-lines-interprocessor-communications-stmicroelectronics.pdf 
+ AN4838 https://www.st.com/resource/en/application_note/an4838-introduction-to-memory-protection-unit-management-on-stm32-mcus-stmicroelectronics.pdf 
+ VsualGDB https://visualgdb.com/tutorials/arm/stm32/multicore/ 
+ How to use LVGL on Riverdi STM32-H7 based Display https://controllerstech.com/lvgl-on-riverdi-stm32-h7-display/#google_vignette 
+ RVT70HSSNWC00-B https://download.riverdi.com/RVT70HSSNWC00-B/DS_RVT70HSSNWC00-B_Rev.1.1.pdf

Final note: CM7 have a memory cache, that can lead to slow responce with shared data, so tell CM7 that SRAM4 is not to be cached, call this code before main loop.
```
void MPU_RegionConfig(void)
{
	MPU_Region_InitTypeDef MPU_InitStruct;
	/* Disable MPU */
	HAL_MPU_Disable();
	/* Configure RAM region as Region N°0, 8kB of size and R/W region */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x38000000; 
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	/* Enable MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
```
