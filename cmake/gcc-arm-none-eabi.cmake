# ============================================================
#  STM32CubeMX 官方推荐 CMake 工具链文件（Cortex-M3 / arm-none-eabi-gcc）
# ============================================================
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "${TOOLCHAIN_PREFIX}gcc")
endif()
if(NOT DEFINED CMAKE_CXX_COMPILER)
  set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")
endif()
if(NOT DEFINED CMAKE_ASM_COMPILER)
  set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}gcc")
endif()
if(NOT DEFINED CMAKE_OBJCOPY)
  set(CMAKE_OBJCOPY "${TOOLCHAIN_PREFIX}objcopy")
endif()
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "${TOOLCHAIN_PREFIX}objdump")
endif()
if(NOT DEFINED CMAKE_SIZE)
  set(CMAKE_SIZE "${TOOLCHAIN_PREFIX}size")
endif()

# 使 try_compile 直接使用交叉编译器而不链接
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 指定 C/C++ 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
