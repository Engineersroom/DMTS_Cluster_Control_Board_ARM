/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TX_MUX_SEL_2_Pin GPIO_PIN_2
#define TX_MUX_SEL_2_GPIO_Port GPIOE
#define TX_MUX_SEL_3_Pin GPIO_PIN_3
#define TX_MUX_SEL_3_GPIO_Port GPIOE
#define TX_MUX_SEL_4_Pin GPIO_PIN_4
#define TX_MUX_SEL_4_GPIO_Port GPIOE
#define TX_MUX_SEL_5_Pin GPIO_PIN_5
#define TX_MUX_SEL_5_GPIO_Port GPIOE
#define TX_MUX_SEL_6_Pin GPIO_PIN_6
#define TX_MUX_SEL_6_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define TX_MUX_SEL_16_Pin GPIO_PIN_0
#define TX_MUX_SEL_16_GPIO_Port GPIOF
#define TX_MUX_SEL_17_Pin GPIO_PIN_1
#define TX_MUX_SEL_17_GPIO_Port GPIOF
#define TX_MUX_SEL_18_Pin GPIO_PIN_2
#define TX_MUX_SEL_18_GPIO_Port GPIOF
#define TX_MUX_SEL_19_Pin GPIO_PIN_3
#define TX_MUX_SEL_19_GPIO_Port GPIOF
#define TX_MUX_SEL_20_Pin GPIO_PIN_4
#define TX_MUX_SEL_20_GPIO_Port GPIOF
#define TX_MUX_SEL_21_Pin GPIO_PIN_5
#define TX_MUX_SEL_21_GPIO_Port GPIOF
#define TX_MUX_SEL_22_Pin GPIO_PIN_6
#define TX_MUX_SEL_22_GPIO_Port GPIOF
#define TX_MUX_SEL_23_Pin GPIO_PIN_7
#define TX_MUX_SEL_23_GPIO_Port GPIOF
#define TX_MUX_SEL_24_Pin GPIO_PIN_8
#define TX_MUX_SEL_24_GPIO_Port GPIOF
#define TX_MUX_SEL_25_Pin GPIO_PIN_9
#define TX_MUX_SEL_25_GPIO_Port GPIOF
#define TX_MUX_SEL_26_Pin GPIO_PIN_10
#define TX_MUX_SEL_26_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define RX_ADDR_0_Pin GPIO_PIN_0
#define RX_ADDR_0_GPIO_Port GPIOC
#define RX_ADDR_1_Pin GPIO_PIN_1
#define RX_ADDR_1_GPIO_Port GPIOC
#define RX_ADDR_2_Pin GPIO_PIN_2
#define RX_ADDR_2_GPIO_Port GPIOC
#define RX_ADDR_3_Pin GPIO_PIN_3
#define RX_ADDR_3_GPIO_Port GPIOC
#define RX_EN_0_Pin GPIO_PIN_0
#define RX_EN_0_GPIO_Port GPIOA
#define RX_EN_1_Pin GPIO_PIN_1
#define RX_EN_1_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define TX_MUX_SEL_27_Pin GPIO_PIN_11
#define TX_MUX_SEL_27_GPIO_Port GPIOF
#define TX_MUX_SEL_28_Pin GPIO_PIN_12
#define TX_MUX_SEL_28_GPIO_Port GPIOF
#define TX_MUX_SEL_29_Pin GPIO_PIN_13
#define TX_MUX_SEL_29_GPIO_Port GPIOF
#define TX_MUX_SEL_30_Pin GPIO_PIN_14
#define TX_MUX_SEL_30_GPIO_Port GPIOF
#define TX_MUX_SEL_31_Pin GPIO_PIN_15
#define TX_MUX_SEL_31_GPIO_Port GPIOF
#define CSA_Pin GPIO_PIN_0
#define CSA_GPIO_Port GPIOG
#define CSB_Pin GPIO_PIN_1
#define CSB_GPIO_Port GPIOG
#define TX_MUX_SEL_7_Pin GPIO_PIN_7
#define TX_MUX_SEL_7_GPIO_Port GPIOE
#define TX_MUX_SEL_8_Pin GPIO_PIN_8
#define TX_MUX_SEL_8_GPIO_Port GPIOE
#define TX_MUX_SEL_9_Pin GPIO_PIN_9
#define TX_MUX_SEL_9_GPIO_Port GPIOE
#define TX_MUX_SEL_10_Pin GPIO_PIN_10
#define TX_MUX_SEL_10_GPIO_Port GPIOE
#define TX_MUX_SEL_11_Pin GPIO_PIN_11
#define TX_MUX_SEL_11_GPIO_Port GPIOE
#define TX_MUX_SEL_12_Pin GPIO_PIN_12
#define TX_MUX_SEL_12_GPIO_Port GPIOE
#define TX_MUX_SEL_13_Pin GPIO_PIN_13
#define TX_MUX_SEL_13_GPIO_Port GPIOE
#define TX_MUX_SEL_14_Pin GPIO_PIN_14
#define TX_MUX_SEL_14_GPIO_Port GPIOE
#define TX_MUX_SEL_15_Pin GPIO_PIN_15
#define TX_MUX_SEL_15_GPIO_Port GPIOE
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define WR_0_Pin GPIO_PIN_0
#define WR_0_GPIO_Port GPIOD
#define WR_1_Pin GPIO_PIN_1
#define WR_1_GPIO_Port GPIOD
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define TX_MUX_SEL_0_Pin GPIO_PIN_0
#define TX_MUX_SEL_0_GPIO_Port GPIOE
#define TX_MUX_SEL_1_Pin GPIO_PIN_1
#define TX_MUX_SEL_1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
