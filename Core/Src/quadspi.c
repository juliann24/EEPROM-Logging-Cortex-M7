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
  hqspi.Init.FifoThreshold = 4;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
  hqspi.Init.FlashSize = 24;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_1_CYCLE;
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
    PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_D1HCLK;
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


HAL_StatusTypeDef QSPI_AutoPollingMemReady(void) {

	QSPI_CommandTypeDef sCommand = { 0 };
	QSPI_AutoPollingTypeDef sConfig = { 0 };
	HAL_StatusTypeDef ret;

	/* Configure automatic polling mode to wait for memory ready ------ */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = W25Q256JV_READ_STATUS_REG1_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
    sCommand.NbData          = 1;    // IMPORTANTE

	sConfig.Match = 0x00;
	sConfig.Mask = 0x01;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.StatusBytesSize = 1;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	if ((ret = HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig,
				HAL_MAX_DELAY)) != HAL_OK) {
			return ret;
		}
	return HAL_OK;
}

HAL_StatusTypeDef QSPI_Default_Init(void) {
	hqspi.Instance = QUADSPI;
	if (HAL_QSPI_DeInit(&hqspi) != HAL_OK) return HAL_ERROR;

	MX_QUADSPI_Init();

	if (QSPI_Set_Status_Config(&hqspi) != HAL_OK) return HAL_ERROR;

	HAL_Delay(100);

	return HAL_OK;
}

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
        return HAL_OK;
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
}

HAL_StatusTypeDef QSPI_WriteEnable(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;
    uint8_t status;

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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

    return QSPI_AutoPollingMemReady();
}

HAL_StatusTypeDef QSPI_Sector_Erase(QSPI_HandleTypeDef *hqspi, uint32_t StartSectorAddress, uint32_t EndSectorAddress)
{
    QSPI_CommandTypeDef sCommand;

    StartSectorAddress = StartSectorAddress
			- StartSectorAddress % W25Q256JV_SECTOR_SIZE;

    EndSectorAddress = EndSectorAddress - (EndSectorAddress % W25Q256JV_SECTOR_SIZE)
                       + (W25Q256JV_SECTOR_SIZE - 1);

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_SECTOR_ERASE_CMD; // 0x20
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
    sCommand.Address           = StartSectorAddress;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

	while (EndSectorAddress >= StartSectorAddress) {
		sCommand.Address = StartSectorAddress;

		if (QSPI_WriteEnable(hqspi) != HAL_OK) {
			return HAL_ERROR;
		}

		if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
				!= HAL_OK) {
			return HAL_ERROR;
		}

		if (QSPI_AutoPollingMemReady() != HAL_OK) {
			return HAL_ERROR;
		}

		StartSectorAddress += W25Q256JV_SECTOR_SIZE;
	}

	return HAL_OK;
}

HAL_StatusTypeDef QSPI_Chip_Erase(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_AutoPollingMemReady() != HAL_OK) return HAL_ERROR;

    if (QSPI_WriteEnable(hqspi) != HAL_OK) return HAL_ERROR;

    memset(&sCommand, 0, sizeof(sCommand));
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
    sCommand.Instruction       = W25Q256JV_CHIP_ERASE_CMD;   // 0xC7 (o 0x60)
    sCommand.AddressMode       = QSPI_ADDRESS_NONE;
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
    sCommand.DataMode          = QSPI_DATA_NONE;
    sCommand.DummyCycles       = 0;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

    if (HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK) return HAL_ERROR;

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
}

HAL_StatusTypeDef QSPI_Write_Data_Quad(QSPI_HandleTypeDef *hqspi,
                                       const uint8_t *pData,
                                       uint32_t size,
                                       uint32_t address)
{
    QSPI_CommandTypeDef sCommand;
    HAL_StatusTypeDef status;
    uint32_t current_addr = address;
    uint32_t end_addr = address + size;
    uint32_t current_size;

    while (current_addr < end_addr)
    {
        // 1️⃣ Calcular cuánto escribir en esta página
        uint32_t addr_in_page = current_addr % W25Q256JV_PAGE_SIZE;
        current_size = W25Q256JV_PAGE_SIZE - addr_in_page;
        if ((end_addr - current_addr) < current_size)
            current_size = end_addr - current_addr;

        // 2️⃣ Habilitar escritura
        if (QSPI_WriteEnable(hqspi) != HAL_OK)
            return HAL_ERROR;

        // 3️⃣ Configurar comando de programación
        memset(&sCommand, 0, sizeof(sCommand));
        sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;
        sCommand.Instruction       = W25Q256JV_PAGE_PROGRAM_QUAD_INPUT_CMD; // 0x32
        sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;
        sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;
        sCommand.Address           = current_addr;
        sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
        sCommand.DataMode          = QSPI_DATA_4_LINES;
        sCommand.DummyCycles       = 0;
        sCommand.NbData            = current_size;
        sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;

        // 4️⃣ Enviar comando + datos
        status = HAL_QSPI_Command(hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
        if (status != HAL_OK)
            return status;

        status = HAL_QSPI_Transmit(hqspi, (uint8_t *)pData, HAL_QPSI_TIMEOUT_DEFAULT_VALUE);
        if (status != HAL_OK)
            return status;

        // 5️⃣ Esperar que termine
        status = QSPI_AutoPollingMemReady();
        if (status != HAL_OK)
            return status;

        // 6️⃣ Avanzar
        current_addr += current_size;
        pData += current_size;
    }

    return HAL_OK;
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

HAL_StatusTypeDef QSPI_Fast_Read_Quad_Output(QSPI_HandleTypeDef *hqspi, uint8_t *pData, uint32_t Address, uint32_t Size)
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

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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
    if (QSPI_AutoPollingMemReady() != HAL_OK)
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
/**
 * @brief Desactiva todos los bits de protección de bloques (BP3..BP0) en el Status Register 1.
 * @param hqspi Puntero al manejador QSPI.
 * @retval HAL_StatusTypeDef HAL_OK si tuvo éxito, HAL_ERROR de lo contrario.
 */
HAL_StatusTypeDef QSPI_Clear_All_BP(QSPI_HandleTypeDef *hqspi)
{
    HAL_StatusTypeDef status;
    uint8_t bp_value = 0;

    // 1️⃣ Leer el valor actual de los BP
    status = QSPI_Check_BP(hqspi, &bp_value);
    if (status != HAL_OK) return status;

    // 2️⃣ Revisar si ya están en 0, si es así no hace falta escribir
    if (bp_value == 0) return HAL_OK;

    // 3️⃣ Escribir 0 en el Status Register 1, solo en los bits BP
    uint8_t sr1_value = 0;

    status = QSPI_Write_Status_Reg1(hqspi, sr1_value);
    if (status != HAL_OK) return status;

    // 4️⃣ Esperar a que la memoria esté lista
    status = QSPI_AutoPollingMemReady();
    if (status != HAL_OK) return status;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_Enter_4Byte_Mode(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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

    if (QSPI_AutoPollingMemReady() != HAL_OK)
        return HAL_ERROR;

    uint8_t ads = 0;
    if (QSPI_Check_4Byte_Mode(hqspi, &ads) == HAL_OK && ads == 1)
        return HAL_OK;

    return HAL_ERROR;
}

HAL_StatusTypeDef QSPI_Exit_4Byte_Mode(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand;

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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

    if (QSPI_AutoPollingMemReady() != HAL_OK)
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
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

    return QSPI_AutoPollingMemReady();
}

HAL_StatusTypeDef QSPI_Set_Status_Config(QSPI_HandleTypeDef *hqspi)
{
	uint8_t status = 0;

	status = QSPI_Software_Reset(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Clear_All_BP(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Enter_4Byte_Mode(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Enable_Quad_Mode(hqspi);
	if (status != HAL_OK) return status;
	status = QSPI_Clear_CMP(hqspi);

	return status;
}

HAL_StatusTypeDef QSPI_DisableMemoryMapped(QSPI_HandleTypeDef *hqspi)
{
    if (HAL_QSPI_Abort(hqspi) != HAL_OK) return HAL_ERROR;

    return QSPI_AutoPollingMemReady();
}

HAL_StatusTypeDef QSPI_ReadStatusAll(QSPI_HandleTypeDef *hqspi, QSPI_StatusRegs_t *status)
{
    if (!status) return HAL_ERROR;
    memset(status, 0, sizeof(QSPI_StatusRegs_t));

    uint8_t sr1 = 0, sr2 = 0, sr3 = 0;

    if (QSPI_Read_Status_Reg1(hqspi, &sr1) != HAL_OK) return HAL_ERROR;
    if (QSPI_Read_Status_Reg2(hqspi, &sr2) != HAL_OK) return HAL_ERROR;
    if (QSPI_Read_Status_Reg3(hqspi, &sr3) != HAL_OK) return HAL_ERROR;

    status->SR1 = sr1;
    status->SR2 = sr2;
    status->SR3 = sr3;

    status->BUSY = sr1 & 0x01;
    status->WEL  = (sr1 >> 1) & 0x01;
    status->BP   = (sr1 >> 2) & 0x1F;   // BP0–BP4

    status->QE   = (sr2 >> 1) & 0x01;
    status->SRL  = (sr2 >> 7) & 0x01;
    status->CMP  = (sr2 >> 6) & 0x01;
    status->LB   = (sr2 >> 3) & 0x03;   // LB bits opcionales según variante

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_SelfTest(QSPI_HandleTypeDef *hqspi, uint32_t address, const char *pattern, uint32_t size)
{
    uint8_t verify_buf[512]; // buffer temporal de lectura
    uint32_t test_size = size;

    if (test_size > W25Q256JV_PAGE_SIZE)
        test_size = W25Q256JV_PAGE_SIZE;

    if (QSPI_AutoPollingMemReady() != HAL_OK) return HAL_ERROR;
    if (QSPI_Set_Status_Config(hqspi) != HAL_OK) return HAL_ERROR;
    if (QSPI_Sector_Erase(hqspi, TEST_ADDR, TEST_ADDR + W25Q256JV_SECTOR_SIZE) != HAL_OK) return HAL_ERROR;
    if (QSPI_Write_String_Quad(hqspi, pattern, TEST_ADDR) != HAL_OK) return HAL_ERROR;
    if (QSPI_Fast_Read_Quad_Output(hqspi, verify_buf, address, test_size) != HAL_OK) return HAL_ERROR;

    if (memcmp(pattern, verify_buf, test_size) != 0) return HAL_ERROR;

    return HAL_OK;
}

HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_1_4(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};

    /* --- Configuración del comando --- */
    sCommand.InstructionMode   = QSPI_INSTRUCTION_1_LINE;   // opcode en 1 línea
    sCommand.Instruction       = 0x6C;                      // Fast Read Quad Output (4-byte)
    sCommand.AddressMode       = QSPI_ADDRESS_1_LINE;       // dirección en 1 línea
    sCommand.AddressSize       = QSPI_ADDRESS_32_BITS;      // 4 bytes de dirección
    sCommand.DataMode          = QSPI_DATA_4_LINES;         // datos en 4 líneas
    sCommand.DummyCycles       = 8;                         // según datasheet (8 dummy típicos)
    sCommand.DdrMode           = QSPI_DDR_MODE_DISABLE;
    sCommand.SIOOMode          = QSPI_SIOO_INST_EVERY_CMD;  // opcode en cada transacción
    sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; // no hay modo bits

    /* --- Configuración de memory-mapped --- */
    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE; // sin timeout
    sMemMappedCfg.TimeOutPeriod     = 0;

    /* --- Habilitar modo Memory-Mapped --- */
    return HAL_QSPI_MemoryMapped(hqspi, &sCommand, &sMemMappedCfg);
}

HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_4_4(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};

    /* --- Configuración del comando --- */
    sCommand.InstructionMode      = QSPI_INSTRUCTION_1_LINE;  // opcode en 1 línea
    sCommand.Instruction          = 0xEC;                     // Fast Read Quad I/O (4-byte)
    sCommand.AddressMode          = QSPI_ADDRESS_4_LINES;     // dirección en 4 líneas
    sCommand.AddressSize          = QSPI_ADDRESS_32_BITS;
    sCommand.AlternateByteMode    = QSPI_ALTERNATE_BYTES_4_LINES; // modo bits en 4 líneas
    sCommand.AlternateBytesSize   = QSPI_ALTERNATE_BYTES_8_BITS;  // 8 bits de modo (generalmente 0x00)
    sCommand.AlternateBytes       = 0x00;                      // modo bits = 0
    sCommand.DataMode             = QSPI_DATA_4_LINES;
    sCommand.DummyCycles          = 4;                         // según datasheet Winbond (6 dummy típicos)
    sCommand.DdrMode              = QSPI_DDR_MODE_DISABLE;
    sCommand.SIOOMode             = QSPI_SIOO_INST_EVERY_CMD;

    /* --- Configuración de memory-mapped --- */
    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    sMemMappedCfg.TimeOutPeriod     = 0;

    /* --- Habilitar modo Memory-Mapped --- */
    return HAL_QSPI_MemoryMapped(hqspi, &sCommand, &sMemMappedCfg);
}

HAL_StatusTypeDef QSPI_EnableMemoryMapped_1_4_4_edit(QSPI_HandleTypeDef *hqspi)
{
    QSPI_CommandTypeDef sCommand = {0};
    QSPI_MemoryMappedTypeDef sMemMappedCfg = {0};

    /* --- Configuración del comando --- */
    sCommand.InstructionMode      = QSPI_INSTRUCTION_1_LINE;      // Opcode por 1 línea
    sCommand.Instruction          = 0xEC;                         // Fast Read Quad I/O (4-byte addr)
    sCommand.AddressMode          = QSPI_ADDRESS_4_LINES;         // Dirección en 4 líneas
    sCommand.AddressSize          = QSPI_ADDRESS_32_BITS;
    sCommand.AlternateByteMode    = QSPI_ALTERNATE_BYTES_4_LINES; // Modo bits en 4 líneas
    sCommand.AlternateBytesSize   = QSPI_ALTERNATE_BYTES_8_BITS;  // 8 bits de modo
    sCommand.AlternateBytes       = 0xFF;                         // Valor recomendado por Winbond
    sCommand.DataMode             = QSPI_DATA_4_LINES;
    sCommand.DummyCycles          = 8;                            // Requerido por W25Q256JV
    sCommand.DdrMode              = QSPI_DDR_MODE_DISABLE;
    sCommand.SIOOMode             = QSPI_SIOO_INST_ONLY_FIRST_CMD; // Solo al inicio (modo continuo)

    /* --- Configuración de Memory-Mapped --- */
    sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
    sMemMappedCfg.TimeOutPeriod     = 0;

    /* --- Activar modo Memory-Mapped --- */
    return HAL_QSPI_MemoryMapped(hqspi, &sCommand, &sMemMappedCfg);
}


HAL_StatusTypeDef QSPI_MemoryMapped_SelfTest(QSPI_HandleTypeDef *hqspi, uint32_t test_addr, const char *test_string)
{
    uint32_t len = strlen(test_string);
    uint8_t read_buffer[W25Q256JV_PAGE_SIZE] = {0};

    if (QSPI_Set_Status_Config(hqspi) != HAL_OK) return HAL_ERROR;

    if (QSPI_Sector_Erase(hqspi, test_addr, test_addr + W25Q256JV_SECTOR_SIZE) != HAL_OK) return HAL_ERROR;

    if (QSPI_Write_Data_Quad(hqspi, (uint8_t *)test_string, len, test_addr) != HAL_OK) return HAL_ERROR;

    if (QSPI_EnableMemoryMapped_1_4_4(hqspi) != HAL_OK) return HAL_ERROR;

    volatile uint8_t *mapped_ptr = (volatile uint8_t *)(QSPI_BASE_ADDR + test_addr);
    for (uint32_t i = 0; i < len; i++) {
        read_buffer[i] = mapped_ptr[i];
    }

    if (memcmp(test_string, read_buffer, len) != 0) return HAL_ERROR;

    return HAL_OK;
}

/* USER CODE END 1 */
