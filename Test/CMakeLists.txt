cmake_minimum_required(VERSION 3.10)

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

#add_executable(
#    Test-static
#    ./src/main.cpp
#    )    

## target_link_libraries(Test HQ)
#target_link_libraries(Test-static)

# message("Boost_LIB: ${Boost_LIBRARIES}") 

# target_link_libraries(Test ${Boost_LIBRARIES} ${OpenCL_LIBRARY})

target_link_libraries(Test ${CONAN_LIBS} ${OpenCL_LIBRARY})


# ${CMAKE_THREAD_LIBS_INIT}