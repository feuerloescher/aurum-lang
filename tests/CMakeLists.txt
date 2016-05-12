# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(aurum_tests)

include_directories("${PROJECT_SOURCE_DIR}/../src/auc")

# TODO: Add macro (or similar) to automatically create an executable
# for each test code file
add_executable(ast_test ast_test.cpp)

target_link_libraries(ast_test auc_lib)
