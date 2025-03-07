#include "bsp.h"
#include "images.h"
#include "main_enum.h"
#include "main_menu.h"
#include "touch_test.h"
#include "hard_test.h"
#include "http_server.h"

#define PLL_M      25      // 외부 25MHz 크리스탈 사용
#define PLL_N      336     // 25MHz * 336 = 8400MHz
#define PLL_P      2       // 8400MHz / 2 = 168MHz (SYSCLK)
#define PLL_Q      7       // USB OTG FS, SDIO, RNG 클럭용 (PLL 출력 / 7)

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  /*
   Since the startup file of the ST firmware library has already executed the CPU system clock initialization, there is no need to configure the system clock again.
   The startup file `startup_stm32f4xx.s` will call the `void SystemInit(void)` function in `system_stm32f4xx.c`.
   The `SystemInit()` function configures the CPU main clock frequency, internal Flash access speed, and optional external SRAM FSMC initialization.
   The main crystal oscillator of the Anfu STM32-V5 development board is 25MHz, and the internal PLL multiplies it to 168MHz.
   If you need to change the main frequency, you can modify the following file:
   `\User\bsp_stm32f4xx\system_stm32f4xx.c`
   Several macros at the beginning of the file are PLL multiplier parameters. By modifying these macros, you can change the main frequency without modifying the hardware.
  */
  uint16_t ucStatus; 

  bsp_Init();
  
  
  //HAL_Init();
  SystemClock_Config();
  //MX_GPIO_Init();
  
  while (1)
  {
    
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

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = PLL_M;
	RCC_OscInitStruct.PLL.PLLN = PLL_N;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = PLL_Q;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            					|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;            // HCLK = SYSCLK = 168MHz
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4; 			      // APB1 = HCLK/4 = 42MHz
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 			      // APB2 = HCLK/2 = 84MHz

	// Flash 레이턴시 설정 (168MHz에서는 5 wait states 필요)
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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

#ifdef  USE_FULL_ASSERT
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
