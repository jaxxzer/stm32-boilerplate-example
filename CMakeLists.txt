cmake_minimum_required(VERSION 3.12)
project(stm32-boilerplate-example)

set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")

set(BOILERPLATE ${PROJECT_SOURCE_DIR}/lib/stm32-boilerplate)
set(LIBOPENCM3 ${BOILERPLATE}/lib/libopencm3)
set(LIBOPENCM3_SRC ${LIBOPENCM3}/lib)

set(COMPILER_FLAGS "-fdata-sections -ffunction-sections -O0 -DNDEBUG -Werror")
set(LINKER_FLAGS "-nostartfiles -specs=nano.specs -specs=nosys.specs --static -ggdb3 -Wl,--gc-sections -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group -Wl,-Map=output.map -T ${BOILERPLATE}/src/link/stm32-mem.ld -L ${BOILERPLATE}/lib/libopencm3/lib")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# target board
if(NOT DEFINED TARGET_BOARD)
  set(TARGET_BOARD "nucleo-f042")
  message("no TARGET_BOARD defined, using ${TARGET_BOARD}")
endif()

# target board directory
set(TARGET_DIR "${PROJECT_SOURCE_DIR}/src/target/${TARGET_BOARD}")

# include target board CMakeLists
include(${TARGET_DIR}/CMakeLists.txt)

# include target board defintions
include_directories(${TARGET_DIR})

# target part
# TODO fail if not set
message("TARGET_MCU: ${TARGET_MCU}")

include(${BOILERPLATE}/src/target-mcu.cmake)

# target architecture
# TODO fail if not set
message("TARGET_CPU: ${TARGET_CPU}")

include_directories(${BOILERPLATE}/lib/libopencm3/include)

set(CMAKE_C_FLAGS "${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMPILER_FLAGS} ${ARCH_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${LINKER_FLAGS} ${ARCH_FLAGS}")

include(${BOILERPLATE}/src/target/f/f.cmake)

set(MAIN_SRC
  src/main.c
  src/io/usart.c
  ${GPIO_SRC}
  ${RCC_SRC}
  ${LIBOPENCM3_SRC}/stm32/common/usart_common_all.c
  ${LIBOPENCM3_SRC}/stm32/common/usart_common_v2.c
  ${LIBOPENCM3_SRC}/cm3/nvic.c
  ${LIBOPENCM3_SRC}/cm3/vector.c
)

set(COMMON_SRC ${BOILERPLATE}/lib/libopencm3/lib/cm3/vector.c)

add_executable(main ${MAIN_SRC} ${COMMON_SRC})

# TODO how to make clean?
add_custom_command(TARGET main POST_BUILD
  COMMAND cp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main debug.elf
)

add_custom_command(TARGET main PRE_LINK
  COMMAND python ${BOILERPLATE}/src/link/generate-ldscript.py -p ${TARGET_MCU} > ${BOILERPLATE}/src/link/stm32-mem.ld
)

# 'make flash' to upload to board after compiling
add_custom_target(flash
  # try stlink v2 first, then stlink v2-1 if that fails
  openocd -f interface/stlink-v2.cfg -f ${OPENOCD_TARGET} -c "program debug.elf verify reset exit" ||
  openocd -f interface/stlink-v2-1.cfg -f ${OPENOCD_TARGET} -c "program debug.elf verify reset exit"
  DEPENDS main
)
