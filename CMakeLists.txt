cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

set(HQ_DIR ${CMAKE_SOURCE_DIR}/HQ)
set(CE_DIR ${CMAKE_SOURCE_DIR}/CE)
set(CLAL_DIR ${CMAKE_SOURCE_DIR}/CLAL)

project(StreamingPrototype)

message("CMAKE_BUILD_TYPE= ${CMAKE_BUILD_TYPE}")
message("CMAKE_SOURCE_DIR= ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR= ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX= ${CMAKE_INSTALL_PREFIX}")

# Srouce dir is HQ and rename it to HQ
add_subdirectory(HQ)
add_subdirectory(CE)
add_subdirectory(CLAL)
add_subdirectory(Test)

# Add test execution in Makefile for testing `make test_run`
enable_testing()
add_test(cl_test
    ${CMAKE_BINARY_DIR}/bin/Test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Test/src
    DEPENDS Test)
