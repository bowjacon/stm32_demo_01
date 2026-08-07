#ifndef STM32F1xx_HAL_CONF_H
#define STM32F1xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* ==================== 模块使能（只保留本工程用到的模块） ==================== */
#define HAL_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED

/* ==================== 晶振/振荡器频率配置 ==================== */
#define HSE_VALUE                    8000000U  /* 外部高速晶振（如需更换请修改） */
#define HSI_VALUE                    8000000U  /* 内部高速振荡器 */
#define LSI_VALUE                    40000U    /* 内部低速振荡器 */
#define LSE_VALUE                    32768U    /* 外部低速晶振 */

#define HSE_STARTUP_TIMEOUT          100U
#define LSE_STARTUP_TIMEOUT          5000U

/* ==================== 系统配置 ==================== */
#define VDD_VALUE                    3300U
#define TICK_INT_PRIORITY            15U
#define USE_RTOS                     0U
#define PREFETCH_ENABLE              1U
#define INSTRUCTION_CACHE_ENABLE     0U
#define DATA_CACHE_ENABLE            0U

#define USE_HAL_ADC_REGISTER_CALLBACKS    0U
#define USE_HAL_CAN_REGISTER_CALLBACKS    0U
#define USE_HAL_CEC_REGISTER_CALLBACKS    0U
#define USE_HAL_DAC_REGISTER_CALLBACKS    0U
#define USE_HAL_ETH_REGISTER_CALLBACKS    0U
#define USE_HAL_EXTI_REGISTER_CALLBACKS   0U
#define USE_HAL_I2C_REGISTER_CALLBACKS    0U
#define USE_HAL_IWDG_REGISTER_CALLBACKS   0U
#define USE_HAL_NAND_REGISTER_CALLBACKS   0U
#define USE_HAL_NOR_REGISTER_CALLBACKS    0U
#define USE_HAL_PCCARD_REGISTER_CALLBACKS 0U
#define USE_HAL_PCD_REGISTER_CALLBACKS    0U
#define USE_HAL_PWR_REGISTER_CALLBACKS    0U
#define USE_HAL_RCC_REGISTER_CALLBACKS    0U
#define USE_HAL_RTC_REGISTER_CALLBACKS    0U
#define USE_HAL_SD_REGISTER_CALLBACKS     0U
#define USE_HAL_SMARTCARD_REGISTER_CALLBACKS 0U
#define USE_HAL_SPI_REGISTER_CALLBACKS    0U
#define USE_HAL_SRAM_REGISTER_CALLBACKS   0U
#define USE_HAL_TIM_REGISTER_CALLBACKS    0U
#define USE_HAL_UART_REGISTER_CALLBACKS   0U
#define USE_HAL_USART_REGISTER_CALLBACKS  0U
#define USE_HAL_WWDG_REGISTER_CALLBACKS   0U

#define USE_SPI_CRC 0U

#define USE_HAL_DMA_REGISTER_CALLBACKS   0U
#define USE_HAL_USB_REGISTER_CALLBACKS   0U

/* ==================== 包含已启用模块的头文件 ==================== */
#ifdef HAL_RCC_MODULE_ENABLED
#include "stm32f1xx_hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "stm32f1xx_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_CORTEX_MODULE_ENABLED
#include "stm32f1xx_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_FLASH_MODULE_ENABLED
#include "stm32f1xx_hal_flash.h"
#endif /* HAL_FLASH_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "stm32f1xx_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
#include "stm32f1xx_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_TIM_MODULE_ENABLED
#include "stm32f1xx_hal_tim.h"
#endif /* HAL_TIM_MODULE_ENABLED */

/* ==================== 调试断言 ==================== */
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif
