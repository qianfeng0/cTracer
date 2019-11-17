cmake_minimum_required(VERSION 2.6)

project(tracerTest)

include_directories(${CTRACER_PATH})

set(LOCAL_SRC_FILES main.cpp)

add_definitions("-g -Wall")

add_executable(tracerTest ${LOCAL_SRC_FILES})
target_link_libraries(tracerTest ctracer pthread)