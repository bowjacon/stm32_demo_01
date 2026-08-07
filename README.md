# stm32_demo01

A breathing LED (LED breathing effect) demo for **STM32F103RCT6**, built with the **STM32 HAL library** and **FreeRTOS**.

The LED brightness fades in and out smoothly using a hardware PWM output, while a FreeRTOS task updates the PWM duty cycle to produce the breathing rhythm.

## Features

- Target MCU: STM32F103RCT6 (Cortex-M3, 256 KB Flash / 48 KB RAM)
- HAL library: STM32CubeF1 v1.8.4
- RTOS: FreeRTOS-Kernel v11.1.0 (ARM_CM3 port)
- Hardware PWM on `TIM3_CH2` (`PB5`), PWM frequency 100 Hz
- Breathing half-cycle 0.5 s (fade up 0.5 s + fade down 0.5 s), full cycle 1.0 s
- LED pin, polarity and breathing timing are configurable in `Core/Inc/led.h`
- Official STM32CubeMX-style CMake project structure
- Buildable with the GNU ARM toolchain (`arm-none-eabi-gcc`)

## Hardware Requirements

- STM32F103RCT6 development board
- One LED wired to `PB5` (active-high by default), or change the pin in `led.h`

> Note: `PB5` is the `TIM3_CH2` alternate function pin. If you change the LED pin,
> make sure the new pin supports the selected timer/PWM channel.

## Project Structure

```
stm32_breathe/
├── CMakeLists.txt                       # Top-level CMake project (official template style)
├── cmake/
│   ├── gcc-arm-none-eabi.cmake          # GNU ARM toolchain file
│   └── stm32cubemx/
│       ├── CMakeLists.txt               # Sources, includes, flags, link script
│       └── stm32cubemx-extras.cmake     # Post-build helpers (hex/bin/size)
├── Core/
│   ├── Inc/
│   │   ├── led.h                        # LED pin & breathing configuration
│   │   ├── main.h
│   │   ├── tim.h
│   │   ├── stm32f1xx_hal_conf.h         # HAL module configuration
│   │   └── FreeRTOSConfig.h             # FreeRTOS kernel configuration
│   └── Src/
│       ├── main.c                       # Clock setup, LED init, FreeRTOS start
│       ├── led.c                        # LED init / brightness control / breath task
│       └── tim.c                        # TIM3 PWM initialization
├── Drivers/
│   ├── CMSIS/                           # CMSIS core & STM32F1xx device files
│   └── STM32F1xx_HAL_Driver/            # STM32 HAL driver
├── Middlewares/FreeRTOS/                # FreeRTOS kernel source
└── STM32F103RCTx_FLASH.ld               # Linker script (256 KB Flash / 48 KB RAM)
```

## Prerequisites

- `cmake` (>= 3.22)
- GNU ARM Embedded Toolchain (`arm-none-eabi-gcc`) on your `PATH`
- A make/ninja build tool (make is used below)

On Debian/Ubuntu, install the tools with:

```bash
sudo apt install cmake gcc-arm-none-eabi
```

## Build

```bash
# 1) Configure (specify the GNU ARM toolchain file)
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
# 2) Build (produces build/BREATH.elf, build/BREATH.hex and build/BREATH.bin)
cmake --build build
# 3) Clean and rebuild (optional)
cmake --build build --target clean
cmake --build build
```

Output artifacts are generated in `build/`:

| File             | Description                          |
| ---------------- | ------------------------------------ |
| `BREATH.elf`     | ELF executable (for debuggers)       |
| `BREATH.bin`     | Raw binary image (flash at 0x08000000) |
| `BREATH.hex`     | Intel HEX file                       |

A typical build prints the memory usage:

```
   text	   data	    bss	    dec	    hex	filename
   8700	     16	   5496	  14212	   3784	build/BREATH.elf
```

## Flash

Flash `build/BREATH.bin` to address `0x08000000` using your preferred tool
(e.g. ST-Link utilities, STM32CubeProgrammer, openOCD, etc.).

## Configuration

All user-configurable settings are in `Core/Inc/led.h`:

```c
#define LED_GPIO_PORT        GPIOB         /* GPIO port of the LED        */
#define LED_GPIO_PIN         GPIO_PIN_5    /* LED pin (default PB5)       */
#define LED_PWM_TIM          TIM3          /* Timer generating PWM        */
#define LED_PWM_CHANNEL      TIM_CHANNEL_2 /* PWM channel (PB5=TIM3_CH2)  */
#define LED_ACTIVE_LEVEL     1             /* 1 = active high, 0 = low    */
#define BREATH_HALF_PERIOD_MS   500        /* breathing half-cycle (ms)   */
#define BREATH_STEPS            100        /* brightness steps per half   */
```

- `LED_ACTIVE_LEVEL` selects the PWM output polarity for the LED wiring.
- `BREATH_HALF_PERIOD_MS` is the time for one fade (up or down). The full
  cycle is `2 * BREATH_HALF_PERIOD_MS` (default 1.0 s).

If you change `LED_GPIO_PORT` / `LED_GPIO_PIN`, also update `LED_PWM_TIM` /
`LED_PWM_CHANNEL` so the timer channel matches the new alternate-function pin.

## How It Works

1. `main.c` initializes the system clock (HSI 8 MHz -> PLL -> 64 MHz), then
   calls `LED_Init()` which configures `PB5` as alternate-function push-pull
   output and starts `TIM3_CH2` PWM (PSC=63, ARR=9999 -> 100 Hz).
2. FreeRTOS is started via `vTaskStartScheduler()`. The `Breath` task runs
   `LED_BreathTask()` in `led.c`.
3. The task sweeps the brightness `0 -> 100` in 100 steps (5 ms per step,
   0.5 s fade-up), then `100 -> 0` (0.5 s fade-down), and repeats forever,
   producing the breathing effect.

## SDK Versions

| Component            | Version                |
| -------------------- | ---------------------- |
| STM32CubeF1 (HAL)    | v1.8.4                 |
| FreeRTOS-Kernel      | v11.1.0                |
| CMSIS                | bundled with CubeF1    |

## License

This project bundles the STM32 HAL library, CMSIS and FreeRTOS-Kernel, which
are distributed under their respective licenses. See the license headers in
each source file.
