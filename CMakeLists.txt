cmake_minimum_required(VERSION 2.6)

project(cTracer)

set(ROOT_PATH ${CMAKE_SOURCE_DIR})
set(CTRACER_PATH ${ROOT_PATH}/libctracer)
# set(XHOOK_PATH ${CTRACER_PATH}/hook/xHook)

# add_subdirectory(hook/xHook)
# add_subdirectory(test)

add_subdirectory(${ROOT_PATH}/libctracer)
add_subdirectory(${ROOT_PATH}/test)