# ============================================================
#  STM32CubeMX CMake 扩展：目标后处理（生成 hex/bin 并打印内存占用）
# ============================================================

function(stm32_cube_helpers TARGET_NAME)
  string(REPLACE ".elf" "" BASE_NAME ${TARGET_NAME})
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET_NAME}> ${BASE_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_NAME}> ${BASE_NAME}.bin
    COMMAND ${CMAKE_SIZE}    $<TARGET_FILE:${TARGET_NAME}>
    COMMENT "Generating ${BASE_NAME}.hex / .bin and printing memory usage"
  )
endfunction()
