cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE debug)

# test
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" CACHE STRING "compile flags" FORCE)

set (CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

set(HQ_DIR ${CMAKE_SOURCE_DIR}/HQ)
set(CE_DIR ${CMAKE_SOURCE_DIR}/CE)
set(CLAL_DIR ${CMAKE_SOURCE_DIR}/CLAL)


project(HeterogeneousQueue)

if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Werror")
endif()


message("CMAKE_BUILD_TYPE= ${CMAKE_BUILD_TYPE}")
message("CMAKE_SOURCE_DIR= ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR= ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX= ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_CXX_STANDARD= ${CMAKE_CXX_STANDARD}")

find_package(OpenCL REQUIRED)

# Source dir is HQ and rename it to HQ
add_subdirectory(HQ)
add_subdirectory(CE)
add_subdirectory(CLAL)
add_subdirectory(Test)

# Add test execution in Makefile for testing `make test_run`
enable_testing()
add_test(NAME cl_test
    COMMAND ${CMAKE_BINARY_DIR}/bin/Test
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/Test/src)
set_tests_properties(cl_test PROPERTIES TIMEOUT 3)

