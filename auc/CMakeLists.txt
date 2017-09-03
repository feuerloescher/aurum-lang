# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(auc)

add_subdirectory(coco-r-cpp)
set(GENERATED_SOURCES
    "${PROJECT_SOURCE_DIR}/Parser/Parser.hpp"
    "${PROJECT_SOURCE_DIR}/Parser/Parser.cpp"
    "${PROJECT_SOURCE_DIR}/Parser/Scanner.hpp"
    "${PROJECT_SOURCE_DIR}/Parser/Scanner.cpp"
    )
add_custom_command(OUTPUT ${GENERATED_SOURCES}
    COMMAND coco-cpp -frames ${PROJECT_SOURCE_DIR}/coco-r-cpp -o ${PROJECT_SOURCE_DIR}/Parser/ -lines ${PROJECT_SOURCE_DIR}/Parser/aurum.atg
    DEPENDS coco-cpp ${PROJECT_SOURCE_DIR}/Parser/aurum.atg
    )

include_directories("${PROJECT_SOURCE_DIR}")

file(GLOB_RECURSE LIB_SOURCES
    "${PROJECT_SOURCE_DIR}/AST/*.cpp"
    "${PROJECT_SOURCE_DIR}/Parser/*.cpp"
    "${PROJECT_SOURCE_DIR}/Passes/*.cpp"
    )

set(MAIN_SRC "${PROJECT_SOURCE_DIR}/main.cpp")

list(INSERT LIB_SOURCES 0 ${GENERATED_SOURCES})

add_library(auc_lib STATIC ${LIB_SOURCES})

add_executable(auc ${MAIN_SRC})
target_link_libraries(auc auc_lib)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} "${PROJECT_SOURCE_DIR}/Doxyfile"
        SOURCES "${PROJECT_SOURCE_DIR}/Doxyfile")
else ()
    message(WARNING "Doxygen is needed to build the documentation.")
endif ()
