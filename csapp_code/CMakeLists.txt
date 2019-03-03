cmake_minimum_required(VERSION 2.6)
project(hostinfo)
# 版本信息
set(hostinfo_VERSION_MAJOR 1)
set(hostinfo_VERSION_MINOR 0)

# 加入一个配置头文件，用于处理 CMake 对源码的设置
configure_file(
		"${PROJECT_SOURCE_DIR}/config.h.in"
		"${PROJECT_BINARY_DIR}/config.h"
		)

# RELEASE
option(RELEASE "-O3" OFF)
# DEBUG
option(DEBUG "-g" ON)

set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")

if(RELEASE)
	SET(CMAKE_BUILE_TYPE "Release")
	message(STATUS "Release -O3 -Wall")
elseif(DEBUG)
	SET(CMAKE_BUILE_TYPE "Debug")
	message(STATUS "Debug -O0 -Wall -g -ggdb")
endif(RELEASE) 


include_directories("${PROJECT_SOURCE_DIR}/include")

#生成可执行程序
add_executable(hostinfo ./netp/hostinfo.c)

# 设置可执行文件输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
