cmake_minimum_required(VERSION 2.6)

project(libcTracer)

set(CTRACER_PATH ${ROOT_PATH}/libctracer)

set(XHOOK_PATH ${CTRACER_PATH}/hook/xHook)
set(COMMON_PATH ${CTRACER_PATH}/common)
set(LEAKCHECK_PATH ${CTRACER_PATH}/leakcheck)


add_definitions("-fPIC -g -Wall")
add_subdirectory(${XHOOK_PATH})
add_subdirectory(${COMMON_PATH})
add_subdirectory(${LEAKCHECK_PATH})

include_directories(./)
add_library(ctracer SHARED ctracer.cpp)
target_link_libraries(ctracer
                        leakcheck xhook common dl)