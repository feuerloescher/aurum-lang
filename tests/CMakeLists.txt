# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(aurum_tests)

include_directories("${PROJECT_SOURCE_DIR}/../src/auc")

# TODO: Add macro (or similar) to automatically create an executable
# for each test code file
add_executable(ast_test ast_test.cpp)
add_test(ast_test ast_test)

target_link_libraries(ast_test auc_lib gcov)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(OUTPUT CMakeFiles/ast_test.dir/ast_test.cpp.gcda
        COMMAND make test
        DEPENDS ast_test)
    add_custom_target(run_coverage_test
        DEPENDS CMakeFiles/ast_test.dir/ast_test.cpp.gcda)

    add_custom_command(OUTPUT coverage.info
        COMMAND rm -f coverage.info
        COMMAND lcov --directory .. --capture --output-file coverage.info
        COMMAND lcov --remove coverage.info 'tests/*' '/usr/*' --output-file coverage.info
        COMMAND lcov --list coverage.info
        DEPENDS CMakeFiles/ast_test.dir/ast_test.cpp.gcda)
    add_custom_target(test_coverage
        DEPENDS coverage.info)
endif()
