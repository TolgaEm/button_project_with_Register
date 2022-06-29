
#include "main.h"

void SystemClock_Config(void);
void led_init(void);
void button_init(void);

uint8_t reader=0;

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  led_init();
  button_init();
  reader = GPIOA->IDR;


  while (1)
  {
    if (reader == 1){
			GPIOD->ODR |= (1 << 15);
			GPIOD->ODR |= (1 << 14);
			GPIOD->ODR |= (1 << 13);
			GPIOD->ODR |= (1 << 12);
    }
    else {
    	GPIOD->ODR &= ~(1 << 15);
    	GPIOD->ODR &= ~(1 << 14);
    	GPIOD->ODR &= ~(1 << 13);
    	GPIOD->ODR &= ~(1 << 12);
    }
  }
}

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
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}



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

void led_init(void){

	// D port clock is enable
	RCC->AHB1ENR = 0X00000008; ;

	// SET OUPUT MODE FOR D12-13-14-15
	GPIOD->MODER = 0X55000000;

	// SET PUSH-PULL MODE
	GPIOD->OTYPER = 0X00000000;

	// SET CLOCK SPEED
	GPIOD->OSPEEDR = 0X55000000;

	// SET NO-PULL
	GPIOD->PUPDR = 0X00000000;
}

void button_init(void){

	// PORT A CLOK ENABLE
	RCC->AHB1ENR = 0X00000001;

	//PORT A SET AS İNPUT
	GPIOA->MODER = 0X00000000;

	// SET AS PULL-PUSH
	GPIOA->OTYPER = 0X00000000;

	// SET CLOCK SPEED (AS HİGH SPEED)
	GPIOA->OSPEEDR = 0X00000002;

	// SET AS A PULL DOWN
	GPIOA->PUPDR = 0X00000002;
}

