cmake_minimum_required(VERSION 2.6)

# Project source dir changes after the project() definition
project(HQ)

include_directories(${CE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)


add_library(
    HQ STATIC
    src/ComputeUnit.cpp
    src/HeterogeneousQueue.cpp
    src/ComputePlatform.cpp
    src/EventSys.cpp
    src/HQ.cpp
    )

