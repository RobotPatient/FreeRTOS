file(GLOB_RECURSE SOURCES src/*.*)
add_library(FreeRTOS ${SOURCES})
target_include_directories(FreeRTOS PUBLIC src/)