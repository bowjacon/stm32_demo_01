# ============================================================
#  STM32CubeMX 官方推荐 CMake 工程配置
#  包含全部源码、头文件、编译选项、链接脚本及后处理命令
# ============================================================

# 若不指定工具链文件，则默认使用官方 gcc-arm-none-eabi 工具链文件
if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CUBE_DIR}/cmake/gcc-arm-none-eabi.cmake")
endif()

include(stm32cubemx-extras)

set(CUBE_NAME "${PROJECT_NAME}.elf")

# ---------------- 汇编源文件 ----------------
set(ASM_SOURCES
  Drivers/CMSIS/Device/ST/STM32F1xx/Source/startup_stm32f103xe.s
)

# ---------------- C 源文件 ----------------
set(C_SOURCES
  Core/Src/main.c
  Core/Src/led.c
  Core/Src/tim.c
  Drivers/CMSIS/Device/ST/STM32F1xx/Source/system_stm32f1xx.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_flash_ex.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_pwr.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim.c
  Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_tim_ex.c
  Middlewares/FreeRTOS/croutine.c
  Middlewares/FreeRTOS/event_groups.c
  Middlewares/FreeRTOS/list.c
  Middlewares/FreeRTOS/queue.c
  Middlewares/FreeRTOS/stream_buffer.c
  Middlewares/FreeRTOS/tasks.c
  Middlewares/FreeRTOS/timers.c
  Middlewares/FreeRTOS/portable/port.c
  Middlewares/FreeRTOS/portable/heap_4.c
)

# ---------------- 头文件搜索路径 ----------------
set(INCLUDES
  Core/Inc
  Drivers/CMSIS/Core/Include
  Drivers/CMSIS/Device/ST/STM32F1xx/Include
  Drivers/STM32F1xx_HAL_Driver/Inc
  Middlewares/FreeRTOS/include
  Middlewares/FreeRTOS/portable
)

# ---------------- 宏定义 ----------------
set(DEFINES
  USE_HAL_DRIVER
  STM32F103xE
)

# ---------------- 编译选项 ----------------
set(FLAGS
  -mcpu=cortex-m3
  -mthumb
  -Wall
  -g
  -O2
  -ffunction-sections
  -fdata-sections
)

# ---------------- 链接选项 ----------------
set(LD_FLAGS
  -T${CUBE_DIR}/STM32F103RCTx_FLASH.ld
  -Wl,--gc-sections
  --specs=nano.specs
  --specs=nosys.specs
)

# ---------------- 目标 ----------------
add_executable(${CUBE_NAME} ${ASM_SOURCES} ${C_SOURCES})

foreach(inc ${INCLUDES})
  target_include_directories(${CUBE_NAME} PUBLIC "${CUBE_DIR}/${inc}")
endforeach()

target_compile_definitions(${CUBE_NAME} PUBLIC ${DEFINES})

target_compile_options(${CUBE_NAME} PUBLIC ${FLAGS})
target_link_options(${CUBE_NAME} PUBLIC ${LD_FLAGS})

# 生成 .hex / .bin 并输出内存占用
stm32_cube_helpers(${CUBE_NAME})
