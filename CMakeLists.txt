# auc - The Aurum compiler
# Copyright (c) 2016  Max Mertens <max.mail@dameweb.de>
# Distributed under the GNU GPL v3. For full terms see the file LICENSE.

cmake_minimum_required(VERSION 2.8)
project(aurum)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)
