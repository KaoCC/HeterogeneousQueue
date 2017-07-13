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

- Create the Makefile

`./Tool/premake/linux64/premake gmake`

- Build it !

`make config=release_x64`