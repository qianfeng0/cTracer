cmake_minimum_required(VERSION 2.6)

project(leakcheck)

include_directories(./)
include_directories(${COMMON_PATH}
)
set(LOCAL_SRC_FILES leakcheck_memory.cpp
)

# add_library(xhook ${LOCAL_SRC_FILES})
add_library(leakcheck STATIC ${LOCAL_SRC_FILES})
