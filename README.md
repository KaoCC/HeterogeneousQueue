# Heterogeneous Queue
The Heterogeneous Queuing Framework


## Build


The following compilers are supported:

- Visual Studio 2015 or 2017

- GCC 5.4

### Windows

- Create Visual Studio 2017 Solution

`./Tool/premake/win/premake5.exe vs2017`


### Linux

1. Create your build directory `mkdir build`
2. Run CMake `cmake ..` for development or `cmake -DCMAKE_BUILD_TYPE=Release` for a release build
3. Compile by running `make`
4. Run test case by `make test_run`


- Build it !

`make config=release_x64`
