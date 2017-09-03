# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)

option(BUILD_WITH_CLANG "Build using the Clang compiler" OFF)

if(BUILD_WITH_CLANG)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
endif()

project(aurum)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_subdirectory(src)
set(CMAKE_CXX_FLAGS_DEBUG
    "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
add_subdirectory(tests)
add_subdirectory(examples)
