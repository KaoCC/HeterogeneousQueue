

# Project source dir changes after the project() definition
# project(cl_test)


# Read More @ https://cmake.org/cmake/help/v3.1/module/FindOpenCL.html
# find_package(OpenCL REQUIRED)
find_package (Threads REQUIRED)

# include_directories(${CE_DIR}/include)
# include_directories(${CLAL_DIR}/include)


include_directories(${OpenCL_INCLUDE_DIR})


# Get rid off annoying OpenCL warning
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-deprecated -Wno-deprecated-declarations")

add_executable(compute_test compute_test.cpp)
add_executable(enqueue_test enqueue_test.cpp)


# add_test(NAME compute_async_test COMMAND compute_test)
add_test(NAME enqueue_hq_test COMMAND enqueue_test)


target_include_directories(compute_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(compute_test ${CONAN_LIBS} ${OpenCL_LIBRARY})
target_compile_features(compute_test PUBLIC cxx_std_17)



target_include_directories(enqueue_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(enqueue_test ${CONAN_LIBS})
target_compile_features(enqueue_test PUBLIC cxx_std_17)


# ${CMAKE_THREAD_LIBS_INIT}


