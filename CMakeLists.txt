# ============================================================
#  STM32CubeMX 风格 CMake 工程（官方推荐模板）
#  编译方法：
#    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/gcc-arm-none-eabi.cmake
#    cmake --build build
# ============================================================
cmake_minimum_required(VERSION 3.22)
project(stm32_demo_01 C CXX ASM)

# custom cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32cubemx")

# stm32 cube project root
set(CUBE_DIR "${CMAKE_CURRENT_LIST_DIR}")

include(cmake/stm32cubemx/CMakeLists.txt)
