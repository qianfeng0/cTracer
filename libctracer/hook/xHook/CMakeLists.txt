cmake_minimum_required(VERSION 2.6)

project(xhook)

set(LOCAL_SRC_FILES xhook.c
                    xh_version.c
                    xh_core.c
                    xh_elf.c
                    xh_log.c
                    xh_util.c)

# add_library(xhook ${LOCAL_SRC_FILES})
add_library(xhook STATIC ${LOCAL_SRC_FILES})