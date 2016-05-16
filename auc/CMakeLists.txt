# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(auc)

file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/*.hpp"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)

set(MAIN_SRC "${PROJECT_SOURCE_DIR}/main.cpp")

list(REMOVE_ITEM SOURCE_FILES ${MAIN_SRC})

add_library(auc_lib STATIC ${SOURCE_FILES})

add_executable(auc ${MAIN_SRC})
target_link_libraries(auc auc_lib)
