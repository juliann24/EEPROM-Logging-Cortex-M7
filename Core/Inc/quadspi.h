/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#include "w25q256jv.h"
#include "string.h"
/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */
// Se recomienda definir un punto de inicio para las pruebas, por ejemplo, el sector 1
#define TEST_ADDRESS 0x00010000


/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef QSPI_Read_JEDEC_ID(QSPI_HandleTypeDef *hqspi, uint8_t *pData);
HAL_StatusTypeDef QSPI_Wait_For_Ready(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Wait_For_Ready_Manual(QSPI_HandleTypeDef *hqspi, uint32_t timeout);
HAL_StatusTypeDef QSPI_Software_Reset(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_Enable_Quad_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Enter_4Byte_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Exit_4Byte_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Write_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t value);
HAL_StatusTypeDef QSPI_Write_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t value);
HAL_StatusTypeDef QSPI_Clear_CMP(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_Sector_Erase(QSPI_HandleTypeDef *hqspi, uint32_t SectorAddress);

HAL_StatusTypeDef QSPI_Write_Data_SPI(QSPI_HandleTypeDef *hqspi, const uint8_t *buffer, uint32_t address, uint32_t size);
HAL_StatusTypeDef QSPI_Write_String_Dual(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address);
HAL_StatusTypeDef QSPI_Write_String_Quad(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address);

HAL_StatusTypeDef QSPI_Read_Data_SPI(QSPI_HandleTypeDef *hqspi, uint8_t *buffer, uint32_t address, uint32_t size);
HAL_StatusTypeDef QSPI_Read_Data_Dual(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);
HAL_StatusTypeDef QSPI_Read_Data_Quad(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);
HAL_StatusTypeDef QSPI_Read_Data_Quad_144(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);

HAL_StatusTypeDef QSPI_Read_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_Read_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_Read_Status_Reg3(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_Check_4Byte_Mode(QSPI_HandleTypeDef *hqspi, uint8_t *is4Byte);
HAL_StatusTypeDef QSPI_Check_QE(QSPI_HandleTypeDef *hqspi, uint8_t *qe_state);
HAL_StatusTypeDef QSPI_Check_BP(QSPI_HandleTypeDef *hqspi, uint8_t *bp_value);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

