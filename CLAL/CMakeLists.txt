cmake_minimum_required(VERSION 2.6)

# Project source dir changes after the project() definition
project(CLAL)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Get rid off annoying OpenCL warning
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-deprecated -Wno-deprecated-declarations")

add_library(
    CLAL STATIC
    ./src/CLParameter.cpp
    ./src/CLPlatform.cpp
    ./src/CLCommandQueue.cpp
    ./src/CLContext.cpp
    ./src/CLBuffer.cpp
    ./src/CLKernel.cpp
    ./src/CLProgram.cpp
    ./src/CLEvent.cpp
    ./src/CLException.cpp
    ./src/CLDevice.cpp
    )

