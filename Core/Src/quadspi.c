/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  /* USER CODE BEGIN QUADSPI_Init 0 */
  /* USER CODE END QUADSPI_Init 0 */

  /* USER CODE BEGIN QUADSPI_Init 1 */
  /* USER CODE END QUADSPI_Init 1 */
  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 1;
  hqspi.Init.FifoThreshold = 1;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 25;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.FlashID = QSPI_FLASH_ID_1;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN QUADSPI_Init 2 */
  /* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */
  /* USER CODE END QUADSPI_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();

    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**QUADSPI GPIO Configuration
    PE2     ------> QUADSPI_BK1_IO2
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    PD12     ------> QUADSPI_BK1_IO1
    PD13     ------> QUADSPI_BK1_IO3
    PB6     ------> QUADSPI_BK1_NCS
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN QUADSPI_MspInit 1 */
  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */
  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();

    /**QUADSPI GPIO Configuration
    PE2     ------> QUADSPI_BK1_IO2
    PB2     ------> QUADSPI_CLK
    PD11     ------> QUADSPI_BK1_IO0
    PD12     ------> QUADSPI_BK1_IO1
    PD13     ------> QUADSPI_BK1_IO3
    PB6     ------> QUADSPI_BK1_NCS
    */
    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13);

  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */
  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

HAL_StatusTypeDef QSPI_Read_JEDEC_ID(QSPI_HandleTypeDef *hqspi, uint8_t *pData)
{
    QSPI_CommandTypeDef sCommand;
    HAL_StatusTypeDef status = HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE; // Instrucción (0x9F) sale por IO0 (MOSI)
    sCommand.Instruction       = W25Q256JV_READ_JEDEC_ID_CMD;  // 0x9F
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;       // No hay fase de dirección
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;        // Datos (3 Bytes) entran por IO1 (MISO)
    sCommand.DummyCycles       = 0;                       // Sin ciclos ficticios
    sCommand.NbData            = W25Q256JV_JEDEC_ID_SIZE;           // Espera 3 bytes de datos
    // sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    // sCommand.DdrHoldHalfCycle  = QSPI_DDR_HALF_CYCLE_DISABLE;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK)
    {
        return status;
    }

    status = HAL_QSPI_Receive(hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK)
    {
        return status;
    }

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Wait_For_Ready_Autopoll(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    QSPI_AutoPollingTypeDef sConfig;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG1_CMD; // 0x05
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;

    sConfig.Match           = 0x00;                                 // Valor esperado es 0 (No Ocupado)
    sConfig.Mask            = W25Q256JV_STATUS_REG1_BUSY_MASK;      // Mascara para el bit BUSY (0x01)
    sConfig.MatchMode       = QSPI_MATCH_MODE_AND;
    sConfig.Interval        = 0x10;
    sConfig.AutomaticStop   = QSPI_AUTOMATIC_STOP_ENABLE;

    return HAL_QSPI_AutoPolling(hqspi, &sCommand, &sConfig, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Wait_For_Ready_Manual(QSPI_HandleTypeDef *hqspi, uint32_t timeout)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t status = 0;
    uint32_t tickstart = HAL_GetTick();

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode 	= QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     	= W25Q256JV_READ_STATUS_REG1_CMD; // 0x05
    sCommand.AddressMode     	= QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode        	= QSPI_DATA_1_LINE;
    sCommand.DummyCycles     	= 0;
    sCommand.NbData          	= 1;

    do {
        if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
            return HAL_ERROR;

        if (HAL_QSPI_Receive(hqspi, &status, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
            return HAL_ERROR;

        if ((HAL_GetTick() - tickstart) > timeout)
            return HAL_TIMEOUT;

    } while (status & W25Q256JV_STATUS_REG1_BUSY_MASK);  // Bit 0 = BUSY

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Read_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t *value)
{
    QSPI_CommandTypeDef sCommand;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG1_CMD; // 0x05
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;     // Los datos (1 byte) vienen en 1 línea
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Read_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t *value)
{
    QSPI_CommandTypeDef sCommand;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG2_CMD;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Read_Status_Reg3(QSPI_HandleTypeDef *hqspi, uint8_t *value)
{
    QSPI_CommandTypeDef sCommand;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG3_CMD;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Enable_Quad_Mode(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t reg_status2 = 0;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG2_CMD;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;


    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;
    if (HAL_QSPI_Receive(hqspi, &reg_status2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;

    if ((reg_status2 & W25Q256JV_STATUS_REG2_QE_MASK) == W25Q256JV_STATUS_REG2_QE_MASK)
    {
        //return HAL_OK;
    }

    memset(&sCommand, 0, sizeof(sCommand));   // <--- IMPORTANTE
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_WRITE_ENABLE_CMD; // 0x06
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    reg_status2 |= W25Q256JV_STATUS_REG2_QE_MASK; // Establecer el Bit QE (0x02)

    sCommand.Instruction       = W25Q256JV_WRITE_STATUS_REG2_CMD;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;
    if (HAL_QSPI_Transmit(hqspi, &reg_status2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Software_Reset(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    HAL_StatusTypeDef status;

    memset(&sCommand, 0, sizeof(sCommand));   // <--- IMPORTANTE
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_ENABLE_RESET_CMD;
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;

    status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK) return status;

    sCommand.Instruction       = W25Q256JV_RESET_DEVICE_CMD;

    status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK) return status;

    return QSPI_Wait_For_Ready_Manual(hqspi,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t status;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_WRITE_ENABLE_CMD; // WRITE ENABLE
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    // Leer SR1 para confirmar WEL=1
    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG1_CMD; // READ STATUS REGISTER-1
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, &status, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (!(status & 0x02)) // Bit 1 = WEL
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi,HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Sector_Erase(QSPI_HandleTypeDef *hqspi, uint32_t SectorAddress)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_SECTOR_ERASE_CMD; // 0x20
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
    sCommand.Address           = SectorAddress;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, W25Q256JV_SECTOR_ERASE_MAX_TIME);
}


HAL_StatusTypeDef QSPI_Write_Data_SPI(QSPI_HandleTypeDef *hqspi, const uint8_t *buffer, uint32_t address, uint32_t size)
{
    QSPI_CommandTypeDef sCommand;

    // 1. Enable Write
    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = W25Q256JV_PAGE_PROGRAM_CMD; // PAGE PROGRAM (1-line)
    sCommand.AddressMode     = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = QSPI_ADDRESS_32_BITS;
    sCommand.Address         = address;
    sCommand.DataMode        = QSPI_DATA_1_LINE;
    sCommand.DummyCycles     = 0;
    sCommand.NbData          = size;
    sCommand.SIOOMode        = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, (uint8_t*)buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Write_Data_Dual(QSPI_HandleTypeDef *hqspi, const uint8_t *buffer, uint32_t address, uint32_t size)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = W25Q256JV_PAGE_PROGRAM_DUAL_INPUT_CMD; // DUAL INPUT PAGE PROGRAM
    sCommand.AddressMode     = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = QSPI_ADDRESS_32_BITS;
    sCommand.Address         = address;
    sCommand.DataMode        = QSPI_DATA_2_LINES;
    sCommand.DummyCycles     = 0;
    sCommand.NbData          = size;
    sCommand.SIOOMode        = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, (uint8_t*)buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Write_String_Dual(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address)
{
    QSPI_CommandTypeDef sCommand;
    uint32_t size = strlen(pString) + 1; // Incluir el NULL terminator
    HAL_StatusTypeDef status;

    if (size > 256) return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = W25Q256JV_WRITE_ENABLE_CMD;
    sCommand.AddressMode     = QSPI_ADDRESS_NONE;
    sCommand.DataMode        = QSPI_DATA_NONE;
    sCommand.DummyCycles     = 0;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;

    // 2. Page Program DUAL Input (0xA2)
    sCommand.Instruction     = W25Q256JV_PAGE_PROGRAM_DUAL_INPUT_CMD;
    sCommand.AddressMode     = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = QSPI_ADDRESS_32_BITS;
    sCommand.Address         = Address;
    sCommand.DataMode        = QSPI_DATA_2_LINES;
    sCommand.NbData          = size;
    sCommand.DummyCycles     = 0;

    status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK) return status;

    status = HAL_QSPI_Transmit(hqspi, (uint8_t *)pString, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK) return status;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Write_String_Quad(QSPI_HandleTypeDef *hqspi, const char *pString, uint32_t Address)
{
    QSPI_CommandTypeDef sCommand;
    uint32_t size = strlen(pString);
    if (size > W25Q256JV_PAGE_SIZE) size = W25Q256JV_PAGE_SIZE;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_PAGE_PROGRAM_QUAD_INPUT_CMD; // 0x32
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
    sCommand.Address           = Address;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;  // escritura en Quad
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = size;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, (uint8_t *)pString, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}


HAL_StatusTypeDef QSPI_Read_Data_SPI(QSPI_HandleTypeDef *hqspi, uint8_t *buffer, uint32_t address, uint32_t size)
{
    QSPI_CommandTypeDef sCommand;
    memset(&sCommand, 0, sizeof(sCommand));

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = W25Q256JV_READ_DATA_CMD; // READ DATA
    sCommand.AddressMode     = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = QSPI_ADDRESS_32_BITS;
    sCommand.Address         = address;
    sCommand.DataMode        = QSPI_DATA_1_LINE;
    sCommand.DummyCycles     = 0;
    sCommand.NbData          = size;
    sCommand.SIOOMode        = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_QSPI_Receive(hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Read_Data_Dual(QSPI_HandleTypeDef *hqspi, uint8_t *buffer, uint32_t address, uint32_t size)
{
    QSPI_CommandTypeDef sCommand;
    memset(&sCommand, 0, sizeof(sCommand));

    sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction     = W25Q256JV_FAST_READ_DUAL_OUT_CMD; // FAST READ DUAL OUTPUT
    sCommand.AddressMode     = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize     = QSPI_ADDRESS_32_BITS;
    sCommand.Address         = address;
    sCommand.DataMode        = QSPI_DATA_2_LINES;
    sCommand.DummyCycles     = 8;
    sCommand.NbData          = size;
    sCommand.SIOOMode        = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_QSPI_Receive(hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Read_Data_Quad(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size)
{
    QSPI_CommandTypeDef sCommand;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_FAST_READ_QUAD_OUT_CMD;  // Fast Read Quad Output (1-1-4)
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
    sCommand.Address           = Address;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.DummyCycles       = 8;     // 8 dummy cycles típicos para 0x6B
    sCommand.NbData            = Size;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_QSPI_Receive(hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Read_Data_Quad_144(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size)
{
    QSPI_CommandTypeDef sCommand;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_FAST_READ_QUAD_IO_CMD; // 0xEB
    sCommand.AddressMode       = QSPI_ADDRESS_4_LINES;
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
    sCommand.Address           = Address;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
    sCommand.AlternateBytes    = 0x00;
    sCommand.AlternateBytesSize= QSPI_ALTERNATE_BYTES_8_BITS;
    sCommand.DataMode          = QSPI_DATA_4_LINES;
    sCommand.DummyCycles       = W25Q256JV_DUMMY_CYCLES_READ_QUAD;  // típicamente 10
    sCommand.NbData            = Size;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return HAL_QSPI_Receive(hqspi, pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}



HAL_StatusTypeDef QSPI_Check_4Byte_Mode(QSPI_HandleTypeDef *hqspi, uint8_t *mode)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t status_reg3 = 0;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));

    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG3_CMD; // READ STATUS REGISTER-3
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, &status_reg3, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (mode != NULL)
        *mode = (status_reg3 & 0x01) ? 1 : 0;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Check_QE(QSPI_HandleTypeDef *hqspi, uint8_t *qe_state)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t reg2 = 0;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG2_CMD;  // READ SR2
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Receive(hqspi, &reg2, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (qe_state)
        *qe_state = (reg2 & 0x02) ? 1 : 0;  // QE = bit 1 de SR2

    return HAL_OK;
}

// Implementación en quadspi.c

/**
 * @brief Lee los bits de protección de bloque (BP3, BP2, BP1, BP0) del Registro de Estado 1 (SR1).
 * @param hqspi Puntero al manejador QSPI.
 * @param bp_value Puntero donde se almacenará el valor de los bits BP (0x3C).
 * @retval HAL_StatusTypeDef Estado de la operación.
 */
HAL_StatusTypeDef QSPI_Check_BP(QSPI_HandleTypeDef *hqspi, uint8_t *bp_value)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t status_reg = 0;
    HAL_StatusTypeDef status;

    // 1. Esperar a que el chip no esté ocupado antes de enviar un comando.
    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    // 2. Configurar el comando para leer el Registro de Estado 1 (0x05)
    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_READ_STATUS_REG1_CMD; // READ STATUS REGISTER 1
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.DummyCycles       = 0;
    sCommand.NbData            = 1;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    // 3. Enviar el comando
    status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK)
        return status;

    // 4. Recibir el valor del registro de estado (SR1)
    status = HAL_QSPI_Receive(hqspi, &status_reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
    if (status != HAL_OK)
        return status;

    // 5. Aplicar la máscara para obtener solo los bits BP
    // W25Q256JV_SR1_BP es 0x3C (0011 1100)
    *bp_value = status_reg & W25Q256JV_SR1_BP;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Enter_4Byte_Mode(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_ENTER_4BYTE_ADDRESS_MODE_CMD; // ENTER 4-BYTE ADDRESS MODE
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    uint8_t ads = 0;
    if (QSPI_Check_4Byte_Mode(hqspi, &ads) == HAL_OK && ads == 1)
        return HAL_OK;

    return HAL_ERROR;
}

HAL_StatusTypeDef QSPI_Exit_4Byte_Mode(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_EXIT_4BYTE_ADDRESS_MODE_CMD; // EXIT 4-BYTE ADDRESS MODE
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    uint8_t ads = 0xFF;
    if (QSPI_Check_4Byte_Mode(hqspi, &ads) == HAL_OK && ads == 0)
        return HAL_OK;

    return HAL_ERROR;
}

HAL_StatusTypeDef QSPI_Write_Status_Reg1(QSPI_HandleTypeDef *hqspi, uint8_t value)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_WRITE_STATUS_REG1_CMD; // 0x01
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1;
    sCommand.DummyCycles       = 0;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, &value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}


HAL_StatusTypeDef QSPI_Write_Status_Reg2(QSPI_HandleTypeDef *hqspi, uint8_t value)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_WRITE_STATUS_REG2_CMD; // 0x31
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 1;
    sCommand.DummyCycles       = 0;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, &value, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Clear_CMP(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t data[2];

    // SR1 = 0x00 → sin BP, sin TB
    // SR2 = 0x02 → QE=1, CMP=0
    data[0] = 0x00;
    data[1] = 0x02;

    if (QSPI_WriteEnable(hqspi) != HAL_OK)
        return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_WRITE_STATUS_REG1_CMD; // Write SR1+SR2 juntos
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.DataMode          = QSPI_DATA_1_LINE;
    sCommand.NbData            = 2;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    if (HAL_QSPI_Transmit(hqspi, data, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
        return HAL_ERROR;

    return QSPI_Wait_For_Ready_Manual(hqspi, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
}

HAL_StatusTypeDef QSPI_Set_Status_Config(QSPI_HandleTypeDef *hqspi)
{
	uint8_t status = 0;

	status = QSPI_Software_Reset(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Enter_4Byte_Mode(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Enable_Quad_Mode(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Clear_CMP(hqspi);

	return status;
}

/* USER CODE END 1 */
