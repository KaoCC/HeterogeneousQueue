cmake_minimum_required(VERSION 3.1)

# Project source dir changes after the project() definition
project(CE)

include_directories(${CLAL_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Get files that should be installed to target prefix
FILE(GLOB PUBLIC_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*)

# Get rid off annoying OpenCL warning
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-deprecated -Wno-deprecated-declarations")

add_library(
    CE STATIC
    ./src/ExecutableSequential.cpp
    ./src/DeviceCLImpl.cpp
    ./src/Device.cpp
    ./src/ComputeEngine.cpp
    ./src/ComputeEngineMix.cpp
    ./src/Executable.cpp
    ./src/FunctionSequential.cpp
    ./src/BufferSequential.cpp
    ./src/ExecutableCLImpl.cpp
    ./src/EventCLImpl.cpp
    ./src/FunctionCLImpl.cpp
    ./src/Buffer.cpp
    ./src/DeviceSequential.cpp
    ./src/ComputeEngineCL.cpp
    ./src/Function.cpp
    )

# Install target
install(TARGETS CE
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )

install(FILES ${PUBLIC_HEADER_FILES}
    DESTINATION include/${PROJECT_NAME}
    )
