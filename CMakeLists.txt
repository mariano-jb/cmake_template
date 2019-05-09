cmake_minimum_required (VERSION 2.8)

# Project name
project(cmake_template)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(BINELF "basic_example.elf")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(PROJECT_HAL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src)
set(PROJECT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/inc)
set(PROJECT_HAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc)
set(PROJECT_CMSIS_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Drivers/CMSIS)
set(PROJECT_MIDDLEWARES_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FatFs/src)
set(PROJECT_ASSEMBLER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/startup)
set(PROJECT_DOCUMENTATION_DIR ${CMAKE_SOURCE_DIR}/documentation)

add_definitions(-DSTM32F407xx)
set(STM32F4_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -mcpu=cortex-m4 -mlittle-endian -mthumb-interwork")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ${STM32F4_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall --std=c++11 ${STM32F4_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/STM32F407VGTx_FLASH.ld --specs=nosys.specs")
enable_language(ASM)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

add_custom_target(deploy
		  COMMAND /usr/bin/openocd -f /usr/share/openocd/scripts/board/stm32f4discovery.cfg -c "program ${EXECUTABLE_OUTPUT_PATH}/${BINELF} verify reset"
		  WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
		  COMMENT "Generating API documentation with Doxygen"
		  VERBATIM)

# The version number
set(cmake_template_VERSION_MAJOR 1)
set(cmake_template_VERSION_MINOR 0)

# Configure a header file to pass some of the CMAKE settings
# to the source code

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_HAL_INCLUDE_DIR}")
include_directories("${PROJECT_CMSIS_INCLUDE_DIR}/Device/ST/STM32F4xx/Include")
include_directories("${PROJECT_CMSIS_INCLUDE_DIR}/Include")
include_directories("${PROJECT_MIDDLEWARES_INCLUDE_DIR}")
include_directories("${PROJECT_MIDDLEWARES_INCLUDE_DIR}/drivers")

add_subdirectory(${PROJECT_DOCUMENTATION_DIR})
add_subdirectory(${PROJECT_HAL_SOURCE_DIR})

add_subdirectory(${PROJECT_SOURCE_MQTT_DIR})

add_executable(	${BINELF} 
		${PROJECT_ASSEMBLER_SOURCE_DIR}/startup_stm32f407xx.s 
		${PROJECT_MIDDLEWARES_INCLUDE_DIR}/drivers/sd_diskio.c 
		${PROJECT_MIDDLEWARES_INCLUDE_DIR}/ff_gen_drv.c 
		${PROJECT_MIDDLEWARES_INCLUDE_DIR}/diskio.c 
		${PROJECT_MIDDLEWARES_INCLUDE_DIR}/ff.c 
		${PROJECT_SOURCE_DIR}/system_stm32f4xx.c 
		${PROJECT_SOURCE_DIR}/stm32f4xx_it.c 
		${PROJECT_SOURCE_DIR}/stm32f4xx_hal_msp.c 
		${PROJECT_SOURCE_DIR}/syscall.c 
		${PROJECT_SOURCE_DIR}/bsp_driver_sd.c 
		${PROJECT_SOURCE_DIR}/fatfs.c 
		${PROJECT_SOURCE_DIR}/SD_management.c 
		${PROJECT_SOURCE_DIR}/main.c)

target_link_libraries(${BINELF} LINK_PUBLIC HAL_LIBRARY)

target_link_libraries(${BINELF} LINK_PUBLIC MQTT_LIBRARY)
