cmake_minimum_required(VERSION 3.1)

# Project source dir changes after the project() definition
project(HQ)

include_directories(${CE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

# add_definitions(-DHQ_STATIC_LIBRARY)

add_definitions(-DHQ_EXPORT_API)

# Get files that should be installed to target prefix
FILE(GLOB PUBLIC_HEADER_FILES ${PROJECT_SOURCE_DIR}/include/*)


add_library(
    HQ SHARED
    src/ComputeUnit.cpp
    src/HeterogeneousQueue.cpp
    src/ComputePlatform.cpp
    src/EventSys.cpp
    src/HQ.cpp
    )

target_link_libraries(HQ CE)

# Install target
install(TARGETS HQ
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
    )

install(FILES ${PUBLIC_HEADER_FILES}
    DESTINATION include/${PROJECT_NAME}
    )
