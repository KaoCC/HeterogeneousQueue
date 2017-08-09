cmake_minimum_required(VERSION 3.1)

# Project source dir changes after the project() definition
project(cl_test)


# Read More @ https://cmake.org/cmake/help/v3.1/module/FindOpenCL.html
# find_package(OpenCL REQUIRED)
find_package (Threads REQUIRED)

include_directories(${CE_DIR}/include)
include_directories(${HQ_DIR}/include)
include_directories(${CLAL_DIR}/include)
# include_directories(${OpenCL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)


# Get rid off annoying OpenCL warning
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-deprecated -Wno-deprecated-declarations")

add_executable(
    Test
    ./src/main.cpp
    )

add_executable(
    Test-static
    ./src/main.cpp
    )    

target_link_libraries(Test CE HQ)
target_link_libraries(Test-static CE-static HQ-static)

# ${CMAKE_THREAD_LIBS_INIT}