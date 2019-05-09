file(GLOB HAL_SRC_FILES *.c)
add_library(HAL_LIBRARY ${HAL_SRC_FILES})

target_include_directories (HAL_LIBRARY PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
