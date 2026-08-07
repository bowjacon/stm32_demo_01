#include "led.h"
#include "tim.h"
#include "FreeRTOS.h"
#include "task.h"

#define LED_PWM_AUTO_RELOAD  ((htim3.Init.Period) + 1U)

void LED_Init(void)
{
  GPIO_InitTypeDef gpio = {0};

  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* LED 引脚配置为复用推挽输出，由 TIM3 的 PWM 驱动 */
  gpio.Pin = LED_GPIO_PIN;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &gpio);

  /* 初始化并启动 TIM3 PWM */
  MX_TIM3_Init();
}

void LED_SetBrightnessPercent(uint8_t percent)
{
  uint32_t pulse;

  if (percent > 100U)
  {
    percent = 100U;
  }

  pulse = (uint32_t)LED_PWM_AUTO_RELOAD * percent / 100U;
  __HAL_TIM_SET_COMPARE(&htim3, LED_PWM_CHANNEL, pulse);
}

void LED_BreathTask(void *argument)
{
  uint16_t i;

  (void)argument;

  for (;;)
  {
    /* 渐亮：亮度 0 -> 100%，耗时 0.5s */
    for (i = 0U; i <= BREATH_STEPS; i++)
    {
      LED_SetBrightnessPercent((uint8_t)i);
      vTaskDelay(pdMS_TO_TICKS(BREATH_STEP_DURATION_MS));
    }

    /* 渐暗：亮度 100 -> 0%，耗时 0.5s */
    for (i = BREATH_STEPS; i > 0U; i--)
    {
      LED_SetBrightnessPercent((uint8_t)i);
      vTaskDelay(pdMS_TO_TICKS(BREATH_STEP_DURATION_MS));
    }
  }
}
