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

typedef struct {
    uint8_t SR1;
    uint8_t SR2;
    uint8_t SR3;

    // Campos interpretados
    uint8_t BUSY;
    uint8_t WEL;
    uint8_t QE;
    uint8_t CMP;
    uint8_t SRL;
    uint8_t BP;
    uint8_t LB;
} QSPI_StatusRegs_t;

#define TEST_ADDR       0x000000      // dirección dentro de la flash
#define TEST_ADDR_2       0x001000      // dirección dentro de la flash
#define QSPI_BASE_ADDR  0x90000000U   // base del mapeo en memoria
#define TEST_STRING     "Hola QSPI!"

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */
HAL_StatusTypeDef QSPI_Read_JEDEC_ID(QSPI_HandleTypeDef *hqspi, uint8_t *pData);
HAL_StatusTypeDef QSPI_Wait_For_Ready(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Wait_For_Ready_Manual(QSPI_HandleTypeDef *hqspi, uint32_t timeout);
HAL_StatusTypeDef QSPI_AutoPollingMemReady(void);
HAL_StatusTypeDef QSPI_Software_Reset(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_Enable_Quad_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Enter_4Byte_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Exit_4Byte_Mode(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Write_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t value);
HAL_StatusTypeDef QSPI_Write_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t value);
HAL_StatusTypeDef QSPI_Clear_CMP(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_Set_Status_Config(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_DisableMemoryMapped(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_1_4(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_4_4(QSPI_HandleTypeDef *hqspi);
HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_4_4_edit(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_Sector_Erase(QSPI_HandleTypeDef *hqspi, uint32_t StartSectorAddress, uint32_t EndSectorAddress);
HAL_StatusTypeDef QSPI_Chip_Erase(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_Write_Data_SPI(QSPI_HandleTypeDef *hqspi, const uint8_t *buffer, uint32_t address, uint32_t size);
HAL_StatusTypeDef QSPI_Write_String_Dual(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address);
HAL_StatusTypeDef QSPI_Write_String_Quad(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address);
HAL_StatusTypeDef QSPI_Write_Data_Quad(QSPI_HandleTypeDef *hqspi, const uint8_t *pData, uint32_t size, uint32_t Address);

HAL_StatusTypeDef QSPI_Read_Data_SPI(QSPI_HandleTypeDef *hqspi, uint8_t *buffer, uint32_t address, uint32_t size);
HAL_StatusTypeDef QSPI_Read_Data_Dual(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);
HAL_StatusTypeDef QSPI_Fast_Read_Quad_Output(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);
HAL_StatusTypeDef QSPI_Read_Data_Quad_144(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size);

HAL_StatusTypeDef QSPI_Read_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_Read_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_Read_Status_Reg3(QSPI_HandleTypeDef *hqspi, uint8_t *pStatus);
HAL_StatusTypeDef QSPI_ReadStatusAll(QSPI_HandleTypeDef *hqspi, QSPI_StatusRegs_t *status);
HAL_StatusTypeDef QSPI_Check_4Byte_Mode(QSPI_HandleTypeDef *hqspi, uint8_t *is4Byte);
HAL_StatusTypeDef QSPI_Check_QE(QSPI_HandleTypeDef *hqspi, uint8_t *qe_state);
HAL_StatusTypeDef QSPI_Check_BP(QSPI_HandleTypeDef *hqspi, uint8_t *bp_value);
HAL_StatusTypeDef QSPI_Clear_All_BP(QSPI_HandleTypeDef *hqspi);

HAL_StatusTypeDef QSPI_SelfTest(QSPI_HandleTypeDef *hqspi, uint32_t address, const char *pattern, uint32_t size);
HAL_StatusTypeDef QSPI_MemoryMapped_SelfTest(QSPI_HandleTypeDef *hqspi, uint32_t test_addr, const char *test_string);
HAL_StatusTypeDef QSPI_MemoryMapped_SelfTest_AllSectors(QSPI_HandleTypeDef *hqspi, const char *test_string, uint32_t sector_step);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

