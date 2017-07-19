cmake_minimum_required(VERSION 2.6)

# Project source dir changes after the project() definition
project(CLAL)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Get files that should be installed to target prefix
FILE(GLOB PUBLIC_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*)

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

# Install target
install(TARGETS CLAL
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )

install(FILES ${PUBLIC_HEADER_FILES}
    DESTINATION include/${PROJECT_NAME}
    )
