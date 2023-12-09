#pragma once

#include <stm32h7xx_hal.h>
#include <fdcan.h>

class CCanBus;
CCanBus *pCanBus;
class CCanBus
{
public:
	CCanBus()
	{
		pCanBus = this; // for intterupt
	}
	
	void Init()
	{
		if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
		{
			//Error_Handler();
		}
		if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			//Error_Handler();
		}		
		
		TxHeader.Identifier = 0x11;
		TxHeader.IdType = FDCAN_STANDARD_ID;
		TxHeader.TxFrameType = FDCAN_DATA_FRAME;
		TxHeader.DataLength = FDCAN_DLC_BYTES_12;
		TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
		TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
		TxHeader.FDFormat = FDCAN_FD_CAN;
		TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
		TxHeader.MessageMarker = 0;
	}
	
	void TickTack()
	{
		for (int i = 0; i < 12; i++)
		{
			TxData[i] = indx++;
		}

		if (HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData) != HAL_OK)
		{
			//Error_Handler();
		}

		HAL_Delay(1000);
	}
	
//private:
	FDCAN_TxHeaderTypeDef   TxHeader;
	FDCAN_RxHeaderTypeDef   RxHeader;
	uint8_t               TxData[12];
	uint8_t               RxData[12];
	int indx = 0;
};

extern "C" void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{
		/* Retreive Rx messages from RX FIFO0 */
		if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &pCanBus->RxHeader, pCanBus->RxData) != HAL_OK)
		{
			/* Reception Error */
//			Error_Handler();
		}
		if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
		{
			/* Notification Error */
			//Error_Handler();
		}
		
		
	}
}
