/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "quadspi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "quadspi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

COM_InitTypeDef BspCOMInit;

/* USER CODE BEGIN PV */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  uint8_t status = 0;
  uint8_t addr_mode = 0;
  uint8_t qe = 0;
  uint8_t aJEDEC_ID[3];
  uint8_t sr1 = 0x00;
  uint8_t sr2 = 0x02;
  uint8_t readsr1 = 0x00;
  uint8_t readsr2 = 0x00;
  uint8_t readsr3 = 0x00;
  const char *test_string = "QUAD_MODE_FUNCIONAL";
  uint32_t string_len = strlen(test_string);
  uint8_t read_buffer[64] = {0};
  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_QUADSPI_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Initialize leds */
  BSP_LED_Init(LED_GREEN);
  BSP_LED_Init(LED_YELLOW);
  BSP_LED_Init(LED_RED);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  BSP_LED_On(LED_YELLOW);
  status = QSPI_Software_Reset(&hqspi);
  if (status != HAL_OK) return status;
  HAL_Delay(1);

  // 2. Esperar que el chip esté listo
  status = QSPI_Wait_For_Ready_Manual(&hqspi, 500);
  if (status != HAL_OK) return status;

  // 3. Leer JEDEC ID para verificar comunicación
  status = QSPI_Read_JEDEC_ID(&hqspi, aJEDEC_ID);
  if (status != HAL_OK) return status;
  if (aJEDEC_ID[0] != W25Q256JV_JEDEC_ID) return HAL_ERROR; // ID del fabricante Winbond (0xEF)

  // 4. Entrar en modo de 4 bytes (comando 0xB7)
  status = QSPI_Enter_4Byte_Mode(&hqspi);
  if (status != HAL_OK) return status;

  status = QSPI_Wait_For_Ready_Manual(&hqspi, 500);
  if (status != HAL_OK) return status;

  // 5. Verificar que realmente entró en modo 4-byte
  status = QSPI_Check_4Byte_Mode(&hqspi, &addr_mode);
  if (status != HAL_OK || addr_mode == 0) return HAL_ERROR;

  // 6. Habilitar modo Quad (QE bit)
  status = QSPI_Enable_Quad_Mode(&hqspi);
  if (status != HAL_OK) return status;

  status = QSPI_Wait_For_Ready_Manual(&hqspi, 500);
  if (status != HAL_OK) return status;

  // 7. Verificar QE
  status = QSPI_Check_QE(&hqspi, &qe);
  if (status != HAL_OK || qe == 0) return HAL_ERROR;

  status = QSPI_Clear_CMP(&hqspi);
  if (status != HAL_OK) return status;

  status = QSPI_Read_Status_Reg1(&hqspi, &readsr1);
  if (status != HAL_OK) return status;
  status = QSPI_Read_Status_Reg2(&hqspi, &readsr2);
  if (status != HAL_OK) return status;
  status = QSPI_Read_Status_Reg3(&hqspi, &readsr3);
  if (status != HAL_OK) return status;


  if (QSPI_Write_Status_Reg1(&hqspi, sr1) != HAL_OK) return HAL_ERROR;

  if (QSPI_Write_Status_Reg2(&hqspi, sr2) != HAL_OK) return HAL_ERROR;


  if (QSPI_Sector_Erase(&hqspi, TEST_ADDRESS) != HAL_OK) Error_Handler();
  if (QSPI_Wait_For_Ready_Manual(&hqspi, 500) != HAL_OK) Error_Handler();

  if (QSPI_Write_String_Quad(&hqspi, test_string, TEST_ADDRESS) != HAL_OK) Error_Handler();
  if (QSPI_Wait_For_Ready_Manual(&hqspi, 500) != HAL_OK) Error_Handler();


  memset(read_buffer, 0, sizeof(read_buffer));
  if (QSPI_Read_Data_Quad(&hqspi, read_buffer, TEST_ADDRESS, string_len) != HAL_OK) Error_Handler();
  if (QSPI_Wait_For_Ready_Manual(&hqspi, 500) != HAL_OK) Error_Handler();

  //////////////////////////////////////////////////////////////////////////
  /////////////////////////////FIN DEL TEST/////////////////////////////////
  //////////////////////////////////////////////////////////////////////////
  if (memcmp(test_string, read_buffer, string_len) == 0)
  {
      // Éxito: Encender LED Verde
      BSP_LED_On(LED_GREEN);
      BSP_LED_Off(LED_RED);
  }
  else
  {
      // Fallo de Lectura/Escritura: Encender LED Rojo
      BSP_LED_On(LED_RED);
      BSP_LED_Off(LED_GREEN);
  }

  while (1)
  {

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_Delay(50);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enables the Clock Security System
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */

  // Si ocurre un error en cualquier paso
  BSP_LED_Off(LED_GREEN);
  BSP_LED_Off(LED_YELLOW);
  BSP_LED_On(LED_RED); // Fallo: LED Rojo Encendido Fijo
  while(1){

  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
