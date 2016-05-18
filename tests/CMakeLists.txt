# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(aurum_tests)

include_directories("${PROJECT_SOURCE_DIR}/../src/auc")

file(GLOB SOURCE_FILES
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)
foreach(src_file ${SOURCE_FILES})
    STRING(REGEX REPLACE ".cpp\$" "" test_name "${src_file}")
    add_executable(${test_name} "${src_file}")
    target_link_libraries(${test_name} auc_lib gcov)
    add_test(${test_name} /bin/bash -c "./${test_name} > ${test_name}.out && (test ! -f ../../tests/${test_name}.out || diff ${test_name}.out ../../tests/${test_name}.out)")
endforeach()

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
