#include "tim.h"
#include "led.h"

TIM_HandleTypeDef htim3;

void MX_TIM3_Init(void)
{
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim3.Instance = TIM3;

  /* 定时器时钟来自 APB1：APB1=32MHz 时 TIM3 时钟为 64MHz。
   * PSC=63 -> 64 分频 -> 1MHz；ARR=9999 -> 100Hz PWM */
  htim3.Init.Prescaler = 63;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

#if (LED_ACTIVE_LEVEL == 1)
  /* 高电平点亮：PWM1 高有效，占空比 = Pulse / (ARR+1) */
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
#else
  /* 低电平点亮：PWM1 低有效，占空比含义反转 */
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
#endif

  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, LED_PWM_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Start(&htim3, LED_PWM_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }
}
