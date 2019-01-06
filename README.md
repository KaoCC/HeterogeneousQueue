# Heterogeneous Queue

The Heterogeneous Queuing Framework for GPU or Memory & IO-intensive tasks


## Dependency

- C++ 17 Compiler
- Conan 1.11
- CMake 3.10
- Boost.Fiber
- Boost.Compute

## Build

The following compilers are tested:

- Clang: Apple LLVM 10.0.0
- Visual Studio 2017 (15.9.4)


### Windows & Linux

1. Create your build directory `mkdir build && cd build`
2. Run Conan `conan install .. -s cppstd=17 --build missing`
3. Run CMake `cmake ..` for development or `cmake -DCMAKE_BUILD_TYPE=Release` for a release build
4. Compile by running `make`
5. Run test case by `make test`

