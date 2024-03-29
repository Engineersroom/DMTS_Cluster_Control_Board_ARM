/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 * 흐음
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USER CODE BEGIN PV */
#define data_length 100
#define Total_Data_Length 9
#define Data_Terminating_Letter 8
#define Data_TX_MUX_SEL_1 3
#define Data_TX_MUX_SEL_2 4
#define Data_RX_MUX_ADDR 6
#define Data_RX_MUX_SEL 7

char UART_RX_data[data_length];
char UART_RX_data_word[8];
char UART_RX_temp[8];
char UART_TX_data = 0;
char uart_flag = 0;
char data_flag = 0;
char uart_cnt = 0;
int cnt = 0;
char received = '\0';
char start_char_flag = 0;
char TX_SEL = 0;
char TX_SEL1 = 0;
char TX_SEL2 = 0;
char RX_ADDR = 0;
char RX_SEL = 0;

HAL_StatusTypeDef rcvStat;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_OTG_FS_PCD_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int __io_putchar(int ch)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  // HAL_UART_Receive_IT(&huart3, &UART_RX_data, 1);

  printf("\r\n----------------------------------------------------------------- \r\n");
  printf("Version 2022, 10, 06 Cluster Control Board Ver 0.0.3 \r\n");
  printf("0.0.1 Labview Communication Test Checked Labview RX\r\n");
  printf("0.0.2 Labview Communication Test Checked Labview TX\r\n");
  printf("0.0.3 Labview Communication Test Checked Data Parsing Test \r\n");
  printf("0.0.4 Git Test  \r\n");
  printf("0.0.5 Labview Communication Test Labview Parsing Test \r\n");
  printf("0.0.6 Labview Communication Test ARM Parsing Test \r\n");
  printf("0.0.7 ARM Protocol Ver 0.1 \r\n");
  printf("0.0.8 Command Added \r\n");
  printf("0.0.9 Function Added \r\n");
  /*GPIO Reset Fuction 추가*/
  printf("0.1.0 Protocal Ver 0.1 \r\n");
  printf("0.1.1 Setting Cluster ID \r\n");
  printf("0.1.2 Setting Chip EN, CS and WR Setting \r\n");
  printf("1.0.0 TX datalenth = 2, so Total data length is 9  \r\n");
  printf("1.0.1 Ratency improve \r\n");
  printf("----- ------------------------------------------------------------ \r\n");
  // HAL_GPIO_WritePin(GPIOE, 0x02, GPIO_PIN_RESET);
  // HAL_GPIO_WritePin(GPIOE, 0x01, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOG, CSA_Pin | CSB_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOD, WR_0_Pin | WR_1_Pin, GPIO_PIN_SET);
  //Test d
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int che = 0;
  int tx_flag = 0;
  char old_sel = 0;
  while (1)
  {

    // UART 신호 수신
    for (int i = 0; i < data_length; i++)
    {
      UART_RX_data[i] = NULL;
    }
    rcvStat = HAL_UART_Receive(&huart3, UART_RX_data, 1, 100);
    TX_SEL = UART_RX_data[0]- 33;
    if (old_sel == TX_SEL)
    {
    }
    else
    {
      if (TX_SEL > 40)
      {
        printf("error : TX_SEL Out Of Range \r\n");
        // HAL_GPIO_WritePin(GPIOE, 0xFF, GPIO_PIN_RESET);
      }
      else if (TX_SEL >= 32) // W 입력 받았을 경우
      {
        HAL_GPIO_WritePin(GPIOE, 0xFF, GPIO_PIN_RESET);
      }
      else if ((TX_SEL >= 16) && (TX_SEL < 32))
      {

        HAL_GPIO_WritePin(GPIOF, 1 << (TX_SEL - 16), GPIO_PIN_SET);
      }
      else if ((TX_SEL > 0) && (TX_SEL < 16))
      {

        HAL_GPIO_WritePin(GPIOE, 0xFF, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, 1 << TX_SEL, GPIO_PIN_SET);
      }
      else if (TX_SEL == 0)
      {
        // printf("%d^%d= %d \r\n", 2, 2, 1 << TX_SEL);
        HAL_GPIO_WritePin(GPIOE, 0xFF, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOE, 0x01, GPIO_PIN_SET);
      }
    }
    old_sel = TX_SEL;
    // else
    // {
    //   HAL_GPIO_WritePin(GPIOE, 0x01, GPIO_PIN_SET);
    //   HAL_Delay(100);
    //   HAL_GPIO_WritePin(GPIOE, 0x01, GPIO_PIN_RESET);
    // }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END 3 */
  }
}
/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */
}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */
}

/**
 * @brief USB_OTG_FS Initialization Function
 * @param None
 * @retval None
 */
static void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */

  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */

  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 4;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */

  /* USER CODE END USB_OTG_FS_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, TX_MUX_SEL_2_Pin | TX_MUX_SEL_3_Pin | TX_MUX_SEL_4_Pin | TX_MUX_SEL_5_Pin | TX_MUX_SEL_6_Pin | TX_MUX_SEL_7_Pin | TX_MUX_SEL_8_Pin | TX_MUX_SEL_9_Pin | TX_MUX_SEL_10_Pin | TX_MUX_SEL_11_Pin | TX_MUX_SEL_12_Pin | TX_MUX_SEL_13_Pin | TX_MUX_SEL_14_Pin | TX_MUX_SEL_15_Pin | TX_MUX_SEL_0_Pin | TX_MUX_SEL_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, TX_MUX_SEL_16_Pin | TX_MUX_SEL_17_Pin | TX_MUX_SEL_18_Pin | TX_MUX_SEL_19_Pin | TX_MUX_SEL_20_Pin | TX_MUX_SEL_21_Pin | TX_MUX_SEL_22_Pin | TX_MUX_SEL_23_Pin | TX_MUX_SEL_24_Pin | TX_MUX_SEL_25_Pin | TX_MUX_SEL_26_Pin | TX_MUX_SEL_27_Pin | TX_MUX_SEL_28_Pin | TX_MUX_SEL_29_Pin | TX_MUX_SEL_30_Pin | TX_MUX_SEL_31_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RX_ADDR_0_Pin | RX_ADDR_1_Pin | RX_ADDR_2_Pin | RX_ADDR_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RX_EN_0_Pin | RX_EN_1_Pin | GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD1_Pin | GPIO_PIN_10 | GPIO_PIN_11 | LD3_Pin | LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, CSA_Pin | CSB_Pin | USB_PowerSwitchOn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, WR_0_Pin | WR_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : TX_MUX_SEL_2_Pin TX_MUX_SEL_3_Pin TX_MUX_SEL_4_Pin TX_MUX_SEL_5_Pin
                           TX_MUX_SEL_6_Pin TX_MUX_SEL_7_Pin TX_MUX_SEL_8_Pin TX_MUX_SEL_9_Pin
                           TX_MUX_SEL_10_Pin TX_MUX_SEL_11_Pin TX_MUX_SEL_12_Pin TX_MUX_SEL_13_Pin
                           TX_MUX_SEL_14_Pin TX_MUX_SEL_15_Pin TX_MUX_SEL_0_Pin TX_MUX_SEL_1_Pin */
  GPIO_InitStruct.Pin = TX_MUX_SEL_2_Pin | TX_MUX_SEL_3_Pin | TX_MUX_SEL_4_Pin | TX_MUX_SEL_5_Pin | TX_MUX_SEL_6_Pin | TX_MUX_SEL_7_Pin | TX_MUX_SEL_8_Pin | TX_MUX_SEL_9_Pin | TX_MUX_SEL_10_Pin | TX_MUX_SEL_11_Pin | TX_MUX_SEL_12_Pin | TX_MUX_SEL_13_Pin | TX_MUX_SEL_14_Pin | TX_MUX_SEL_15_Pin | TX_MUX_SEL_0_Pin | TX_MUX_SEL_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_Btn_Pin */
  GPIO_InitStruct.Pin = USER_Btn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_Btn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TX_MUX_SEL_16_Pin TX_MUX_SEL_17_Pin TX_MUX_SEL_18_Pin TX_MUX_SEL_19_Pin
                           TX_MUX_SEL_20_Pin TX_MUX_SEL_21_Pin TX_MUX_SEL_22_Pin TX_MUX_SEL_23_Pin
                           TX_MUX_SEL_24_Pin TX_MUX_SEL_25_Pin TX_MUX_SEL_26_Pin TX_MUX_SEL_27_Pin
                           TX_MUX_SEL_28_Pin TX_MUX_SEL_29_Pin TX_MUX_SEL_30_Pin TX_MUX_SEL_31_Pin */
  GPIO_InitStruct.Pin = TX_MUX_SEL_16_Pin | TX_MUX_SEL_17_Pin | TX_MUX_SEL_18_Pin | TX_MUX_SEL_19_Pin | TX_MUX_SEL_20_Pin | TX_MUX_SEL_21_Pin | TX_MUX_SEL_22_Pin | TX_MUX_SEL_23_Pin | TX_MUX_SEL_24_Pin | TX_MUX_SEL_25_Pin | TX_MUX_SEL_26_Pin | TX_MUX_SEL_27_Pin | TX_MUX_SEL_28_Pin | TX_MUX_SEL_29_Pin | TX_MUX_SEL_30_Pin | TX_MUX_SEL_31_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : RX_ADDR_0_Pin RX_ADDR_1_Pin RX_ADDR_2_Pin RX_ADDR_3_Pin */
  GPIO_InitStruct.Pin = RX_ADDR_0_Pin | RX_ADDR_1_Pin | RX_ADDR_2_Pin | RX_ADDR_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RX_EN_0_Pin RX_EN_1_Pin PA2 */
  GPIO_InitStruct.Pin = RX_EN_0_Pin | RX_EN_1_Pin | GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD1_Pin PB10 PB11 LD3_Pin
                           LD2_Pin */
  GPIO_InitStruct.Pin = LD1_Pin | GPIO_PIN_10 | GPIO_PIN_11 | LD3_Pin | LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : CSA_Pin CSB_Pin USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = CSA_Pin | CSB_Pin | USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : WR_0_Pin WR_1_Pin */
  GPIO_InitStruct.Pin = WR_0_Pin | WR_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART3)
  {
    // ?��?��?�� 1개�?? ?��?��?���? ?��?��?��?���? 발생?��?��?��.
    // HAL_UART_Receive_IT(&huart3, &UART_RX_data, 1);
    // HAL_UART_Transmit(&huart3, &UART_RX_data, 1, 1000);
    // uart_flag = 1;
  }
}
void GPIO_Reset()
{
  HAL_GPIO_WritePin(GPIOE, TX_MUX_SEL_2_Pin | TX_MUX_SEL_3_Pin | TX_MUX_SEL_4_Pin | TX_MUX_SEL_5_Pin | TX_MUX_SEL_6_Pin | TX_MUX_SEL_7_Pin | TX_MUX_SEL_8_Pin | TX_MUX_SEL_9_Pin | TX_MUX_SEL_10_Pin | TX_MUX_SEL_11_Pin | TX_MUX_SEL_12_Pin | TX_MUX_SEL_13_Pin | TX_MUX_SEL_14_Pin | TX_MUX_SEL_15_Pin | TX_MUX_SEL_0_Pin | TX_MUX_SEL_1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOF, TX_MUX_SEL_16_Pin | TX_MUX_SEL_17_Pin | TX_MUX_SEL_18_Pin | TX_MUX_SEL_19_Pin | TX_MUX_SEL_20_Pin | TX_MUX_SEL_21_Pin | TX_MUX_SEL_22_Pin | TX_MUX_SEL_23_Pin | TX_MUX_SEL_24_Pin | TX_MUX_SEL_25_Pin | TX_MUX_SEL_26_Pin | TX_MUX_SEL_27_Pin | TX_MUX_SEL_28_Pin | TX_MUX_SEL_29_Pin | TX_MUX_SEL_30_Pin | TX_MUX_SEL_31_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, RX_ADDR_0_Pin | RX_ADDR_1_Pin | RX_ADDR_2_Pin | RX_ADDR_3_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA, RX_EN_0_Pin | RX_EN_1_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOG, CSA_Pin | CSB_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOD, WR_0_Pin | WR_1_Pin, GPIO_PIN_RESET);
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
