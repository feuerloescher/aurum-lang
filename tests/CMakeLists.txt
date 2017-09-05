# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(aurum_tests)

include_directories("${PROJECT_SOURCE_DIR}/../auc")

file(GLOB SOURCE_FILES
    RELATIVE "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/*.cpp"
)
foreach(src_file ${SOURCE_FILES})
    STRING(REGEX REPLACE ".cpp\$" "" test_name "${src_file}")
    add_executable(${test_name} "${src_file}")
    target_link_libraries(${test_name} auc_lib gcov ${llvm_libs})
    add_test(${test_name} "${PROJECT_SOURCE_DIR}/test.sh" "${test_name}")
endforeach()

if(BUILD_WITH_CLANG)
    set(GCOV_TOOL "${PROJECT_SOURCE_DIR}/llvm-gcov.sh")
else()
    set(GCOV_TOOL "gcov")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(OUTPUT CMakeFiles/ast_test.dir/ast_test.cpp.gcda
        COMMAND make test
        DEPENDS ast_test)
    add_custom_target(run_coverage_test
        DEPENDS CMakeFiles/ast_test.dir/ast_test.cpp.gcda)

    add_custom_command(OUTPUT coverage.info
        COMMAND rm -f coverage.info
        COMMAND lcov --directory .. --capture --output-file coverage.info --gcov-tool "${GCOV_TOOL}"
        COMMAND lcov --remove coverage.info 'tests/*' '/usr/*' '/tmp/*' --output-file coverage.info
        COMMAND lcov --list coverage.info
        DEPENDS CMakeFiles/ast_test.dir/ast_test.cpp.gcda)
    add_custom_target(test_coverage
        DEPENDS coverage.info)
endif()
