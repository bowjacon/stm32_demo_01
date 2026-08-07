#ifndef LED_H
#define LED_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================
 * 呼吸灯引脚配置（根据你的实际硬件自行修改）
 *
 * 默认：LED 接在 PB5，使用 TIM3_CH2 硬件 PWM 输出。
 * 注意：更换引脚时需要同时修改 LED_PWM_TIM / LED_PWM_CHANNEL，
 *       使其对应一个具备 PWM 输出能力的引脚（复用功能）。
 *       例如 PB0 = TIM3_CH3，PA7 = TIM1_CH1N 等。
 * ================================================================ */
#define LED_GPIO_PORT        GPIOB         /* LED 所在 GPIO 端口       */
#define LED_GPIO_PIN         GPIO_PIN_5    /* LED 引脚号（默认 PB5）   */
#define LED_PWM_TIM          TIM3          /* 产生 PWM 的定时器        */
#define LED_PWM_CHANNEL      TIM_CHANNEL_2 /* PWM 通道（PB5=TIM3_CH2） */
#define LED_ACTIVE_LEVEL     1             /* 1=高电平点亮，0=低电平点亮 */

/* ================================================================
 * 呼吸参数配置
 * 要求：呼吸半周期 0.5s（渐亮 0.5s + 渐暗 0.5s = 完整循环 1s）
 * ================================================================ */
#define BREATH_HALF_PERIOD_MS   500        /* 呼吸半周期时长 (ms) */
#define BREATH_STEPS            100        /* 半周期内的亮度步数  */
#define BREATH_STEP_DURATION_MS (BREATH_HALF_PERIOD_MS / BREATH_STEPS)

/* 初始化 GPIO 复用功能与定时器 PWM */
void LED_Init(void);

/* 设置亮度百分比（0-100），供呼吸任务/外部调用 */
void LED_SetBrightnessPercent(uint8_t percent);

/* FreeRTOS 呼吸灯任务入口 */
void LED_BreathTask(void *argument);

#ifdef __cplusplus
}
#endif

#endif
