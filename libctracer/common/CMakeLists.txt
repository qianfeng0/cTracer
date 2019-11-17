cmake_minimum_required(VERSION 2.6)

project(common)

include_directories(./)

set(LOCAL_SRC_FILES unwind_backtrace.cpp
                    virtual_heap.cpp
                    stack_warp.cpp
                    virtual_heap.cpp
)

# add_library(xhook ${LOCAL_SRC_FILES})
add_library(common STATIC ${LOCAL_SRC_FILES})