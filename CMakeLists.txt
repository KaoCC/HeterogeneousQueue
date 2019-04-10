cmake_minimum_required(VERSION 3.11)


# test
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" CACHE STRING "compile flags" FORCE)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)


project(HeterogeneousQueue LANGUAGES CXX)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4)  #/WX
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic)  #-Werror
endif()

message("CMAKE_CXX_COMPILER_ID= ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_BUILD_TYPE= ${CMAKE_BUILD_TYPE}")
message("CMAKE_SOURCE_DIR= ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR= ${CMAKE_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX= ${CMAKE_INSTALL_PREFIX}")
message("CMAKE_CXX_STANDARD= ${CMAKE_CXX_STANDARD}")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# set(Boost_DEBUG ON)

find_package(OpenCL REQUIRED)
# find_package(Boost 1.69.0 REQUIRED COMPONENTS system thread fiber)

# message("Boost_LIB: ${Boost_LIBRARIES}") 




# Add test execution in Makefile for testing `make test_run`
enable_testing()
add_subdirectory(test)


