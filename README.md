# Heterogeneous Queue
The Heterogeneous Queuing Framework


## Build

### Windows
- Create Visual Studio 2015 Solution

`./Tool/premake/win/premake5.exe vs2015`


### Linux
On Ubuntu or Debian:
install gcc (or clang):

`sudo apt-get install g++`

create the Makefile:

`./Tools/premake/linux64/premake5 gmake`

`make CXX=g++ CXXFLAGS=-std=c++11`

